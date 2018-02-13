#pragma once
#include "tile.h"

class Write: public Tile{
public:
  Vec2 pos;

  Write(const Vec2 &pos);

  void add_dot(Dot *dot);
};