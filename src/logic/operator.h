#pragma once
#include "../vec2.h"

// forward declaration
class Dot;

class Operator{
public:
	// local position in circuits
	Vec2 pos;

	Operator(const Vec2 &pos);

	// called by the stepper when a dot arrives at this operator
	void add_dot(Dot &dot);
};