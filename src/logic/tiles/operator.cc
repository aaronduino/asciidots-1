#include "operator.h"
#include "../dot.h"

Operator::Operator(const Vec2 &pos, const char &opChar, const bool &vertical):
Tile(pos){
  this->pos = pos;
  this->opChar = opChar;
  this->vertical = vertical;
}

void Operator::add_dot(Dot *dot){
  dot->state = STATE_DISABLED;

  // dot isn't parallel to operator
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
		case '%':
			return lhs % rhs;
		case '&':
			return lhs & rhs;
		case '|':
			return lhs | rhs;
		case '^':
			return lhs ^ rhs;
		case '>':
			return lhs > rhs ? 1 : 0;
		case 'G':
			return lhs >= rhs ? 1 : 0;
		case '<':
			return lhs < rhs ? 1 : 0;
		case 'L':
			return lhs <= rhs ? 1 : 0;
		case '=':
			return lhs == rhs ? 1 : 0;
		case '!':
			return lhs != rhs ? 1 : 0;
		default:
			return lhs;
	}
}