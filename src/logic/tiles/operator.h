#pragma once
#include "tile.h"
#include <queue>

// takes horizontal and vertical dots. when there's a pair, it operates on them
class Operator: public Tile{
public:
  Vec2 pos;

  // opChar is the character of the operation, e.g. +, -, ^
  // vertical is true for [] operators, false for {}.
  // primary dot is always released when there's a pair, secondary killed
  Operator(const Vec2 &pos, const char &opChar, const bool &vertical);

  void add_dot(Dot *dot);

private:
  char opChar;
  bool vertical;

  std::queue<Dot*> primary;
  std::queue<Dot*> secondary;

  int operate(const int &lhs, const int &rhs);
};