#pragma once
#include "../../vec2.h"

#define TILE_BRANCH   0
#define TILE_CLONE    1
#define TILE_FLOW     2
#define TILE_OPERATOR 3
#define TILE_READ     4
#define TILE_WRITE    5

// forward dec
class Dot;

/* base class for all tile objects
   children must implement add_dot method which is called when dots arrive here
   tiles remember their local position for testing arrival */
class Tile{
public:
  Vec2 pos; // local position of this tile within its circuit

  Tile(const Vec2 &p) : pos(p) {} // pos must be set in constructor

  virtual void add_dot(Dot *dot) = 0;
  virtual int get_type() = 0; // tiles must report their type
};