#include "vec2.h"

Vec2::Vec2(const int &value){
	x = y = value;
}

Vec2::Vec2(const int &xValue, const int &yValue){
	x = xValue;
	y = yValue;
}

Vec2 Vec2::operator +=(const Vec2 &rhs){
	x += rhs.x;
	y += rhs.y;
	return *this;
}
Vec2 operator +(Vec2 lhs, const Vec2 &rhs){
	lhs += rhs;
	return rhs;
}

Vec2 Vec2::operator -=(const Vec2 &rhs){
	x -= rhs.x;
	y -= rhs.y;
	return *this;
}
Vec2 operator -(Vec2 lhs, const Vec2 &rhs){
	lhs -= rhs;
	return rhs;
}