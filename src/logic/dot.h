#pragma once
#include "../vec2.h"

// states
#define STATE_NONE      0
#define STATE_HASH      1
#define STATE_AT        2
#define STATE_READVALUE 3
#define STATE_READID    4
#define STATE_WRITE     5
#define STATE_DISABLED  6
#define STATE_DEAD      7
#define STATE_SKIP      8
#define STATE_CLONE     9

class Dot{
public:
	// vector position and normalised direction
	Vec2 pos, dir;
	// track state between ticks
	int state = STATE_NONE;

	// value and ID init to 0
	int value = 0;
	int id = 0;

	Dot(Vec2 pos, Vec2 dir);
	Dot(const Dot &dot); // clone constructor

	// take one step forward
	void move();

	// turn positive or negative multiples of 90 degrees
	void turn(int turns);
};