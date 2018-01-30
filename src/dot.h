#pragma once
#include "vec2.h"

class Dot{
public:
	Vec2 pos, dir;

	// initialise with position and direction vectors
	Dot(const Vec2 &pos, const Vec2 &dir);

	// move one space forwards
	void move();
};