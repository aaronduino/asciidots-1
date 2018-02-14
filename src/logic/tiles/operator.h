#pragma once
#include "tile.h"
#include <queue>

/* operates on two dots: one horizontal, one vertical
   primary dot is parallel to the operator: horizontal for {}, vertical for []
   primary is lhs of operator, secondary is rhs.
   primary gets the result of the operation, secondary gets killed
   dots will queue up horizontally or vertically until a partner arrives */
class Operator: public Tile{
public:
  Vec2 pos;

  /* opChar is the character of the operation, e.g. +, -, ^
     vertical is true for [] operators, false for {}. */
  Operator(const Vec2 &pos, const char &opChar, const bool &vertical);

  void add_dot(Dot *dot);

private:
  char opChar;
  bool vertical;

  std::queue<Dot*> primary;
  std::queue<Dot*> secondary;

  int operate(const int &lhs, const int &rhs);
};