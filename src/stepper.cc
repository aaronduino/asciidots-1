#include "stepper.h"
#include "circuittools.h"
#include "tiletools.h"
#include "point.h"

using namespace std;

Stepper::Stepper(vector<string> circuit){
  this->circuit = circuit;
}

void Stepper::Step(vector<Dot> *dots){
  vector<Dot> &dotsR = *dots;
  vector<Dot> cloneBuffer; // ensures clones don't step this tick

  // do all dots once every tick
  for(int i = 0; i < dotsR.size(); i++){

    dotsR[i].Move();

    // for convenience
    Point pos = dotsR[i].position;
    int dir = dotsR[i].GetDirection();
    bool hor = dotsR[i].IsHorizontal();
    bool ver = !hor;

    if(!WithinBounds(pos, circuit) ||
       !ValidEntry(circuit[pos.y][pos.x], dir)){
         
      dotsR.erase(dotsR.begin()+i); // remove i-th element
      i--; // since removing an element shifts all back by one
      continue; // dot's dead, next
    }

    // do after bounds check to avoid out of bounds crash
    char tile = circuit[pos.y][pos.x];

    switch(tile){

      case '\\':
        if(hor)
          dotsR[i].Turn(1);
        else
          dotsR[i].Turn(-1);
        break;
      case '/':
        if(ver)
          dotsR[i].Turn(1);
        else
          dotsR[i].Turn(-1);
        break;

      case '<':
        if(ver)
          dotsR[i].PointTo(3);
        break;
      case '>':
        if(ver)
          dotsR[i].PointTo(1);
        break;
      case '^':
        if(hor)
          dotsR[i].PointTo(0);
        break;
      case 'v':
        if(hor)
          dotsR[i].PointTo(2);
        break;

      case '*':
        if(hor){
          cloneBuffer.push_back(dotsR[i].Clone(0));
          cloneBuffer.push_back(dotsR[i].Clone(2));
        }
        else{
          cloneBuffer.push_back(dotsR[i].Clone(1));
          cloneBuffer.push_back(dotsR[i].Clone(3));
        }
        break;
    }
  }

  // add the clone buffer to the dot list
  dotsR.insert(dotsR.end(), cloneBuffer.begin(), cloneBuffer.end());
}
