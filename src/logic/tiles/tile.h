#pragma once
#include "../../vec2.h"

// forward dec
class Dot;

class Tile{
public:
	// local position of this tile within its circuit
	Vec2 pos;

	// ensure pos is always set at construction
	Tile(const Vec2 &p) : pos(p) {}

	virtual void add_tile(Dot *dot) = 0;
};