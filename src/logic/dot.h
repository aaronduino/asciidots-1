#pragma once
#include "../vec2.h"

// states
#define STATE_NONE      0
#define STATE_HASH      1
#define STATE_AT        2
#define STATE_READVALUE 3
#define STATE_READID    4
#define STATE_WRITE     5
#define STATE_DISABLED  6
#define STATE_DEAD      7
#define STATE_SKIP      8
#define STATE_CLONE     9

class Dot{
public:
  Vec2 pos, dir; // local position and normalised direction
  int state = STATE_NONE; // remember state between steps
  int value = 0; // can be read/written/processed
  int id = 0; // can be read/written but not processed

  Dot(Vec2 pos, Vec2 dir);
  Dot(const Dot &dot); // clone constructor

  void move(); // take one step forward
  void turn(int turns); // turn in multiples of right angles
};