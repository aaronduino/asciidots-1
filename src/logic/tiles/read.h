#pragma once
#include "tile.h"

// gets dots into reading mode on # and @ tiles
class Read: public Tile{
public:
  Vec2 pos;

  Read(const Vec2 &pos, const char &readType);

  void add_dot(Dot *dot);
  int get_type();

private:
  char readType;
};