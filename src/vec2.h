#pragma once

// integer order 2 vector
struct Vec2{
public:
	// values
	int x, y;

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