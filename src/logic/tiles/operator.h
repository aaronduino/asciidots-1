#pragma once
#include "tile.h"
#include <queue>

class Operator: public Tile{
public:
  Vec2 pos;

  Operator(const Vec2 &pos, const char &opChar, const bool &vertical);

  void add_dot(Dot *dot);

private:
  char opChar;
  bool vertical;

  std::queue<Dot*> primary;
  std::queue<Dot*> secondary;

  int operate(const int &lhs, const int &rhs);
};