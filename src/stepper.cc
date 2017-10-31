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

  // do all dots once every tick
  for(int i = 0; i < dotsR.size(); i++){

    dotsR[i].Move();

    // for convenience
    Point pos = dotsR[i].position;
    int dir = dotsR[i].GetDirection();
    bool hor = dotsR[i].IsHorizontal();
    bool ver = !hor;
    char tile = circuit[pos.y][pos.x];

    if(!WithinBounds(pos, circuit) || !ValidEntry(tile, dir)){
      dotsR.erase(dotsR.begin()+i); // remove i-th element
      i--; // since removing an element shifts all back by one
      continue; // dot's dead, next
    }


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
    }
  }
}
