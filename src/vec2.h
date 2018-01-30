#pragma once

// two component integer vector
class Vec2{
public:
	// values
	int x, y;

	// constructors
	Vec2(const int &value = 0);
	Vec2(const int &xValue, const int &yValue);

	// operators
	// addition
	Vec2 operator +(const Vec2 &rhs){
		return Vec2(x + rhs.x, y + rhs.y);
	}
	Vec2 operator +=(const Vec2 &rhs){
		*this = *this + rhs;
		return *this;
	}
};

