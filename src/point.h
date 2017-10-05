#pragma once
struct Point{
  int x, y;

  Point operator +(const Point& rhs){
    Point point;
    point.x = this->x + rhs.x;
    point.y = this->y + rhs.y;
    return point;
  }

  Point operator -(const Point& rhs){
    Point point;
    point.x = this->x - rhs.x;
    point.y = this->y - rhs.y;
    return point;
  }

  Point& operator +=(const Point& rhs){
    this->x += rhs.x;
    this->y += rhs.y;
    return *this;
  }

  Point& operator -=(const Point& rhs){
    this->x -= rhs.x;
    this->y -= rhs.y;
    return *this;
  }

  bool operator ==(const Point& rhs){
    return this->x == rhs.x && this->y == rhs.y;
  }

  bool operator !=(const Point& rhs){
    return this->x != rhs.x || this->y != rhs.y;
  }
};
