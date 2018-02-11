#include "operator.h"
#include "dot.h"

Operator::Operator(const Vec2 &pos, const char &opChar, const bool &vertical){
	this->pos = pos;
	this->opChar = opChar;
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
		// just convenient
		auto p = primary.back();
		auto s = secondary.back();

		// release primary, kill secondary
		p->state = STATE_NONE;
		s->state = STATE_DEAD;

		// operate on values, give primary the result
		p->value = operate(p->value, s->value);

		// primary has been released, but don't let it move this step
		p->state = STATE_SKIP;

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

int Operator::operate(const int &lhs, const int &rhs){
	switch(opChar){
		case '+':
			return lhs + rhs;
		case '-':
			return lhs - rhs;
		case '*':
			return lhs * rhs;
		case '/':
			return lhs / rhs;
		default:
			return lhs;
	}
}