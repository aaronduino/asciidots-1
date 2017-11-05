#pragma once
#include <iostream>
#include <memory>
#include "dot.h"
#include "point.h"

class Operator{
public:
  Operator(Point position, char opChar, bool horizontal);

  Point position;

  void AddDot(Dot &dot);

private:
  char opChar;
  bool horizontal;

  bool holding = false;
  Dot *heldDot;

  double Operate(double lhs, double rhs);
};
