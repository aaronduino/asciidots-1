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
		// for now release both. TODO: kill one
		primary.back()->state = STATE_NONE;
		secondary.back()->state = STATE_NONE;

		// forget them, they're gone
		primary.pop();
		secondary.pop();
	}
}