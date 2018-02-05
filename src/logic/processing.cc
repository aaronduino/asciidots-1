#include "circuit.h"
#include "dot.h"

bool Circuit::step(){
	if(dots.size() == 0)
		return false;

	// holds clones to be spawned at the end of the tick
	std::vector<Dot> clones;

	for(uint32_t i = 0; i < dots.size(); i++){
		// move this dot
		dots[i].move();

		// what tile did it land on
		char tile = get_tile(dots[i].pos.y, dots[i].pos.x);

		// if we landed on empty or illegally entered a tile, die
		if(tile == ' ' || !valid_travel(tile, dots[i].dir)){
			dots.erase(dots.begin()+i);
			i--; // everything shifts down, so go back one
			continue;
		}

		// TILE PROCESSING
		// reading logic
		if(dots[i].state == STATE_NONE){
			if(tile == '#')
				dots[i].state = STATE_HASH;
			else if(tile == '@')
				dots[i].state = STATE_AT;
		}
		// last tile was a #, if this tile's a digit we're starting a read
		else if(dots[i].state == STATE_HASH){
			if(tile >= '0' && tile <= '9'){ // is this tile a digit
				dots[i].state = STATE_READVALUE;
				dots[i].value = 0; // prepare for a new value
			}
			else // false alarm
				dots[i].state = STATE_NONE;
		}
		// last tile was an @, if this tile's a digit we're starting a read
		else if(dots[i].state == STATE_AT){ // same for ID. TODO: don't repeat code
			if(tile >= '0' && tile <= '9'){
				dots[i].state = STATE_READID;
				dots[i].id = 0;
			}
			else
				dots[i].state = STATE_NONE;
		}

		// we're currently doing reading
		// if this tile's a digit, read it and skip processing
		// if it's not a digit, stop reading and process tile normally
		if(dots[i].state == STATE_READVALUE){
			if(tile >= '0' && tile <= '9'){ // is this tile another digit to read
				dots[i].value *= 10; // shift all digits left
				dots[i].value += tile - '0'; // tack on the new digit
				continue; // don't do any other processing for this tile
			}
			else
				dots[i].state = STATE_NONE;
		} // exactly the same but for ID not value. TODO: don't repeat code
		else if(dots[i].state == STATE_READID){
			if(tile >= '0' && tile <= '9'){
				dots[i].id *= 10;
				dots[i].id += tile - '0';
				continue;
			}
			else
				dots[i].state = STATE_NONE;
		}

		// process this tile
		if(dots[i].state == STATE_NONE){
			// change directions
			process_flow(tile, dots[i]);

			// load clones into buffer for next tick
			if(tile == '*'){
				clones.push_back(Dot(dots[i]));
				clones[clones.size()-1].turn(-1);
				clones.push_back(Dot(dots[i]));
				clones[clones.size()-1].turn(1);
			}
		}
	}

	// spawn the clones in the buffer
	while(clones.size() > 0){
		dots.push_back(clones[0]);
		clones.erase(clones.begin());
	}

	return true;
}

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