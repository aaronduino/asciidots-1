#include <ctype.h>
#include "stepper.h"
#include "circuittools.h"
#include "tiletools.h"
#include "point.h"

using namespace std;

Stepper::Stepper(vector<string> circuit, vector<Operator> ops){
  this->circuit = circuit;
  this->ops = ops;
}

vector<string> Stepper::Step(vector<Dot> &dots){
  vector<string> out;

  cloneBuffer.clear();

  // do all dots once every tick
  for(int i = 0; i < dots.size(); i++){

    if(!dots[i].enabled || dots[i].deathMarked)
      continue; // this dot shouldn't be updating

    dots[i].Move();

    // for convenience
    Point pos = dots[i].position;
    int dir = dots[i].GetDirection();

    // is this dot now in a deathly situation?

    if(!WithinBounds(pos, circuit)){
      dots[i].deathMarked = true;
      continue;
    }

    // do after bounds check to avoid out of bounds crash
    char tile = circuit[pos.y][pos.x];

    if(!ValidEntry(tile, dir)){
      dots[i].deathMarked = true;
      continue;
    }

    // does the dot's new position require any actions?

    FlowCheck(dots[i], tile);
    CloneCheck(dots[i], tile);
    OperatorCheck(dots[i]);
    ReadCheck(dots[i], tile);
    vector<string> outputs = WriteCheck(dots[i], tile);
    out.insert(out.end(), outputs.begin(), outputs.end());
  }

  // kill all dots marked for death on this cycle
  for(int i = 0; i < dots.size(); i++){
    if(dots[i].deathMarked){
      dots.erase(dots.begin()+i);
      i--; // otherwise we'd skip a dot when they shift down
    }
  }

  // add the clone buffer to the dot list
  dots.insert(dots.end(), cloneBuffer.begin(), cloneBuffer.end());
  return out;
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

void Stepper::OperatorCheck(Dot &dot){
  for(int i = 0; i < ops.size(); i++){
    if(ops[i].position == dot.position)
      return ops[i].AddDot(dot);
  }
}

void Stepper::ReadCheck(Dot &dot, char tile){
  if(tile == '#' && dot.state == none){
    dot.state = read;
    dot.value = 0;
    return;
  }

  if(dot.state == read){
    if(isdigit(tile)){
      dot.value *= 10;
      dot.value += tile - 48; // convert tile to a number
    }
    else
      dot.state = none;
  }
}

vector<string> Stepper::WriteCheck(Dot &dot, char tile){
  vector<string> out;

  if(tile == '$' && dot.state == none){
    dot.state = write;
    return vector<string> {};
  }

  if(dot.state == write){
    if(tile == '#')
      out.push_back(to_string(dot.value));
    else
      dot.state = none;
  }

  return out;
}
