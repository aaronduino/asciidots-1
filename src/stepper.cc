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

    // kill before sentancing more
    if(dotsR[i].deathMarked){
      dotsR.erase(dotsR.begin()+i); // remove i-th element
      i--; // since removing an element shifts all back by one
      continue; // dot's dead, next
    }

    dotsR[i].Move();

    // for convenience
    Point pos = dotsR[i].position;
    int dir = dotsR[i].GetDirection();

    if(!WithinBounds(pos, circuit)){
      dotsR[i].deathMarked = true;
      continue;
    }

    char tile = circuit[pos.y][pos.x];

    // should we not have entered this tile this way? die
    if(!ValidEntry(tile, dir)){
      dotsR[i].deathMarked = true;
      continue;
    }
  }
}
