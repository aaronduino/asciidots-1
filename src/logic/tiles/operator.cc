#include "operator.h"
#include "../dot.h"

Operator::Operator(const Vec2 &pos, const char &opChar, const bool &vertical):
Tile(pos){
  this->opChar = opChar;
  this->vertical = vertical;
}

void Operator::add_dot(Dot *dot){
  dot->state = STATE_DISABLED;

  if(vertical ^ (dot->dir.x == 0)) // dot isn't parallel to operator
    secondary.push(dot);
  else
    primary.push(dot);

  while(primary.size() > 0 && secondary.size() > 0){ // if there's a pair
    auto p = primary.back(); // convenience
    auto s = secondary.back();

    p->state = STATE_NONE; // release primary but don't let it move this step
    s->state = STATE_DEAD; // kill secondary

    p->value = operate(p->value, s->value); // operate on vals, give p result

    primary.pop();
    secondary.pop();
  }
}

int Operator::operate(const int &lhs, const int &rhs){
	switch(opChar){
		case '+':
			return lhs + rhs; // add
		case '-':
			return lhs - rhs; // sub
		case '*':
			return lhs * rhs; // mult
		case '/':
			return lhs / rhs; // div
		case '%':
			return lhs % rhs; // mod
		case '&':
			return lhs & rhs; // AND
		case '|':
			return lhs | rhs; // OR
		case '^':
			return lhs ^ rhs; // XOR
		case '>':
			return lhs > rhs ? 1 : 0; // greater than
		case 'G':
			return lhs >= rhs ? 1 : 0; // greater than or equal
		case '<':
			return lhs < rhs ? 1 : 0; // less than
		case 'L':
			return lhs <= rhs ? 1 : 0; // less than or equal
		case '=':
			return lhs == rhs ? 1 : 0; // equal
		case '!':
			return lhs != rhs ? 1 : 0; // not equal
		default:
			return lhs;
	}
}