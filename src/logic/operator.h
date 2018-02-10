#pragma once
#include <queue>
#include <set>
#include "../vec2.h"

// forward declaration
class Dot;

class Operator{
public:
	// local position in circuits
	Vec2 pos;

	// vertical is true for {x} and false for [x]
	Operator(const Vec2 &pos, const char &opChar, const bool &vertical);

	// called by the stepper when a dot arrives at this operator
	void add_dot(Dot *dot);

	// is tile in the validOpChars set
	static bool valid_op_char(const char &tile);

private:
	// hold dots that come in via add_dot
	// primary dots come in parallel to the exit, eg primary is horizontal for {}
	std::queue<Dot*> primary;
	std::queue<Dot*> secondary;

	// true for [] ops, false for {} ops
	bool vertical;

	// the character that represents this operator
	char opChar;

	// set of all valid operator characters
	static std::set<char> validOpChars;

	// perform this op's calculation
	int operate(const int &lhs, const int &rhs);
};