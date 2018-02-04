#include "circuit.h"
#include "dot.h"

void Circuit::process_flow(const char &tile, Dot &dot){
	switch(tile){
			// FLOW
			case '\\':
				if(dot.dir.y == 0) // horizontal
					dot.turn(1);
				else
					dot.turn(-1);
				break;
			case '/':
				if(dot.dir.x == 0) // vertical
					dot.turn(1);
				else
					dot.turn(-1);
				break;
			case '(': // bounce
			case '>': // both have same behaviour, brackets just kill verticals
				dot.dir = Vec2(1, 0);
				break;
			case ')':
			case '<':
				dot.dir = Vec2(-1, 0);
				break;
			case 'v':
				dot.dir = Vec2(0, 1);
				break;
			case '^':
				dot.dir = Vec2(0, -1);
				break;
		}
}