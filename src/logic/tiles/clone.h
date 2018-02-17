#pragma once
#include "tile.h"

// sets dot states to STATE_CLONE, signalling a split
class Clone: public Tile{
public:
  Vec2 pos;

  Clone(const Vec2 &pos);
  
  void add_dot(Dot *dot);
  int get_type();
};