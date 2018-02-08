#include "operator.h"
#include "dot.h"

Operator::Operator(const Vec2 &pos){
	this->pos = pos;
}

void Operator::add_dot(Dot &dot){
	dot.state = STATE_DISABLED;
}