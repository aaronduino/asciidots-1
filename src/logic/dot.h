#pragma once
#include "../vec2.h"

class Dot{
public:
	// vector position and normalised direction
	Vec2 pos, dir;

	Dot(Vec2 pos, Vec2 dir);
	Dot(const Dot &dot); // clone constructor

	// take one step forward
	void move();

	// turn positive or negative multiples of 90 degrees
	void turn(int turns);
};