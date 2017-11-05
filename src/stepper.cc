#include "stepper.h"
#include "circuittools.h"
#include "tiletools.h"
#include "point.h"

using namespace std;

Stepper::Stepper(vector<string> circuit){
  this->circuit = circuit;
}

void Stepper::Step(vector<Dot> &dots){
  cloneBuffer.clear();

  // do all dots once every tick
  for(int i = 0; i < dots.size(); i++){

    dots[i].Move();

    // for convenience
    Point pos = dots[i].position;
    int dir = dots[i].GetDirection();

    if(!WithinBounds(pos, circuit) ||
       !ValidEntry(circuit[pos.y][pos.x], dir)){

      dots.erase(dots.begin()+i); // remove i-th element
      i--; // since removing an element shifts all back by one
      continue; // dot's dead, next
    }

    // do after bounds check to avoid out of bounds crash
    char tile = circuit[pos.y][pos.x];

    FlowCheck(dots[i], tile);
    CloneCheck(dots[i], tile);
  }

  // add the clone buffer to the dot list
  dots.insert(dots.end(), cloneBuffer.begin(), cloneBuffer.end());
}

void Stepper::FlowCheck(Dot &dot, char tile){
  bool hor = dot.IsHorizontal();

  // various direction changing tiles
  if(tile=='\\' || tile=='/'){
    int turn = 1;
    if(hor) turn *= -1;
    if(tile=='\\') turn *= -1;

    dot.Turn(turn);
  }
  else if(tile=='^' || tile=='>' || tile=='v' || tile=='<'){
    int dir = 0;

    if(tile=='>') dir = 1;
    else if(tile=='v') dir = 2;
    else if(tile=='<') dir = 3;

    dot.PointTo(dir);
  }
  else if(tile=='(')
    dot.PointTo(1);
  else if(tile==')')
    dot.PointTo(3);
}

void Stepper::CloneCheck(Dot dot, char tile){
  if(tile != '*')
    return;

  int rot = 0;
  if(dot.IsVertical()) rot++;

  cloneBuffer.push_back(dot.Clone(rot));
  cloneBuffer.push_back(dot.Clone(rot+2));
}
