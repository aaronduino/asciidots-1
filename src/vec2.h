#pragma once

// vector of two integers: x and y
struct Vec2{
public:
  int x, y; // values

  Vec2(const int &value = 0);
  Vec2(const int &xValue, const int &yValue);

  // operators
  // addition
  Vec2 operator +=(const Vec2 &rhs);
  friend Vec2 operator +(Vec2 lhs, const Vec2 &rhs);

  // subtraction
  Vec2 operator -=(const Vec2 &rhs);
  friend Vec2 operator -(Vec2 lhs, const Vec2 &rhs);

  // equality
  bool operator ==(const Vec2 &rhs);
  bool operator !=(const Vec2 &rhs);
};