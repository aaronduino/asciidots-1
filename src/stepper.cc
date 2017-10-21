#include "stepper.h"
#include "circuittools.h"
#include "tiletools.h"
#include "point.h"

using namespace std;

Stepper::Stepper(vector<string> circuit, vector<Dot> dots){
  this->circuit = circuit;
  this->dots = dots;
}

void Stepper::Step(){
  // do all dots once every tick
  for(int i = 0; i < dots.size(); i++){

    // kill before sentancing more
    if(dots[i].deathMarked){
      dots.erase(dots.begin()+i); // remove i-th element
      i--; // since removing an element shifts all back by one
      continue; // dot's dead, next
    }

    dots[i].Move();

    // for convenience
    Point pos = dots[i].position;
    int dir = dots[i].GetDirection();

    if(!WithinBounds(pos, circuit)){
      dots[i].deathMarked = true;
      continue;
    }

    char tile = circuit[pos.y][pos.x];

    // should we not have entered this tile this way? die
    if(!ValidEntry(tile, dir)){
      dots[i].deathMarked = true;
      continue;
    }
  }
}
