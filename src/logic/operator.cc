#include "operator.h"
#include "dot.h"

Operator::Operator(const Vec2 &pos, const bool &vertical){
	this->pos = pos;
	this->vertical = vertical;
}

void Operator::add_dot(Dot *dot){
	dot->state = STATE_DISABLED;

	// misaligned
	if(vertical ^ (dot->dir.x == 0))
		secondary.push(dot);
	else
		primary.push(dot);

	// release if there are pairs
	while(primary.size() > 0 && secondary.size() > 0){
		// release primary, kill secondary
		primary.back()->state = STATE_NONE;
		secondary.back()->state = STATE_DEAD;

		// forget them, they're gone
		primary.pop();
		secondary.pop();
	}
}

bool Operator::valid_op_char(const char &tile){
	return validOpChars.find(tile) != validOpChars.end();
}

std::set<char> Operator::validOpChars = {
	'+', '-', '*', '/'
};