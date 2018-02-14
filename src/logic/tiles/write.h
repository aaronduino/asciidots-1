#pragma once
#include "tile.h"

// gets a dot into writing when it hits a $ tile
class Write: public Tile{
public:
  Vec2 pos;

  Write(const Vec2 &pos);

  void add_dot(Dot *dot);
};