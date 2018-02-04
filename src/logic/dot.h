#pragma once
#include "../vec2.h"

class Dot{
public:
	// vector position and normalised direction
	Vec2 pos, dir;

	Dot(Vec2 pos, Vec2 dir);
};