#pragma once
#include "../../vec2.h"

// forward dec
class Dot;

/* base class for all tile objects
   children must implement add_dot method which is called when dots arrive here
   tiles remember their local position for testing arrival */
class Tile{
public:
  // local position of this tile within its circuit
  Vec2 pos;

  // ensure pos is always set at construction
  Tile(const Vec2 &p) : pos(p) {}

  virtual void add_dot(Dot *dot) = 0;
};