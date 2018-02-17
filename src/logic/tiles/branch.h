#pragma once
#include "tile.h"
#include <queue>

/* essentially a branch if zero. takes two dots: vertical and horizontal.
   if vertical's value is zero, horizontal will take its direction.
   if vertical's value is anything else, horizontal will continue straight.
   vertical dot is always killed after it's used. */
class Branch: public Tile{
public:
  Vec2 pos;

  Branch(const Vec2 &pos);

  void add_dot(Dot *dot);
  int get_type();

private:
  std::queue<Dot*> primary; // always horizontal
  std::queue<Dot*> secondary; // always vertical
};