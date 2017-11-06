#pragma once
#include "point.h"

enum dotState { none, read, write };

class Dot{
public:
  Point position;

  bool enabled = true; // whether the dot should be stepped
  bool deathMarked = false; // indicates this dot should be killed

  double value = 0;

  dotState state = none;

  Dot(Point position, int direction);
  Dot(Point position, Point vDir); // accept init with vector

  int GetDirection() { return direction; } // prevents setting dir over/under

  void PointTo(int direction); // also sets vector
  void PointTo(Point vDir); // also sets clock
  void Turn(int turns); // quarter turns clockwise

  void Move() { position += vDir; } // travel one space in vDir

  bool IsHorizontal() { return (this->direction & 1) == 1; } // odd clock
  bool IsVertical() { return (this->direction & 1) == 0; } // even clock

  Dot Clone(int newDir); // give a similar dot pointing in a given dir

private:
  int direction; // clock direction (0 up, 1 right, 2 down, 3 left)
  Point vDir { 0, 0 }; // vector direction (x, y)
};
