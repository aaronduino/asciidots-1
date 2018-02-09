#include "circuit.h"
#include "dot.h"
#include "../io/io.h"

/*
 * contains tile processing logic for the Circuit class
 */

bool Circuit::step(){
	if(dots.size() == 0)
		return false;

	// holds clones to be spawned at the end of the tick
	std::vector<Dot*> clones;

	for(uint32_t i = 0; i < dots.size(); i++){
		// don't do anything with disabled dots
		if(dots[i]->state == STATE_DISABLED)
			continue;

		// move this dot
		dots[i]->move();

		// what tile did it land on
		char tile = get_tile(dots[i]->pos.y, dots[i]->pos.x);

		// if we landed on empty or illegally entered a tile, die
		if(tile == ' ' || !valid_travel(tile, dots[i]->dir)){
			dots[i]->state = STATE_DEAD;
			continue;
		}

		// TILE PROCESSING
		// should we prepare to start reading
		if(process_read_mode(tile, *dots[i]))
			continue;

		// should we be reading this tile as a digit
		if(process_reading(tile, *dots[i]))
			continue;

		// should we be doing any outputting
		if(process_writing(tile, *dots[i]))
			continue;

		// process this tile
		if(dots[i]->state == STATE_NONE){
			// is there an operator on this tile
			for(uint32_t j = 0; j < ops.size(); j++){
				if(ops[j].pos == dots[i]->pos){
					ops[j].add_dot(dots[i]);
					continue;
				}
			}
			
			// should we be changing direction
			if(process_flow(tile, *dots[i]))
				continue;

			// should we be cloning here
			if(tile == '*'){
				// add clones to a buffer so they're not active this step
				clones.push_back(new Dot(*dots[i]));
				clones[clones.size()-1]->turn(-1);
				clones.push_back(new Dot(*dots[i]));
				clones[clones.size()-1]->turn(1);
			}
		}
	}

	// remove dots with state STATE_DEAD
	for(uint32_t i = 0; i < dots.size(); i++){
		if(dots[i]->state == STATE_DEAD){
			dots.erase(dots.begin() + i);
			i--;
		}
	}

	// spawn the clones from the buffer
	while(clones.size() > 0){
		dots.push_back(clones[0]);
		clones.erase(clones.begin());
	}

	return true;
}

bool Circuit::process_flow(const char &tile, Dot &dot){
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
			default: // nothing was affected, more processing can be done
				return false;
		}
	return true; // one of the cases hit, no subsequent processing required
}

bool Circuit::process_read_mode(const char &tile, Dot &dot){
	if(dot.state == STATE_NONE){
		if(tile == '#'){
			dot.state = STATE_HASH;
			return true;
		}
		else if(tile == '@'){
			dot.state = STATE_AT;
			return true;
		}
	}
	// last tile was a #, if this tile's a digit we're starting a read
	else if(dot.state == STATE_HASH){
		if(tile >= '0' && tile <= '9'){ // is this tile a digit
			dot.state = STATE_READVALUE;
			dot.value = 0; // prepare for a new value
		}
		else // false alarm, we're not going to read
			dot.state = STATE_NONE;
	}
	// last tile was an @, if this tile's a digit we're starting a read
	else if(dot.state == STATE_AT){ // same for ID. TODO: don't repeat code
		if(tile >= '0' && tile <= '9'){
			dot.state = STATE_READID;
			dot.id = 0;
		}
		else
			dot.state = STATE_NONE;
	}

	return false;
}

bool Circuit::process_reading(const char &tile, Dot &dot){
	// we're currently doing reading
	// if this tile's a digit, read it and skip processing
	// if it's not a digit, stop reading and process tile normally
	if(dot.state == STATE_READVALUE){
		if(tile >= '0' && tile <= '9'){ // is this tile another digit to read
			dot.value *= 10; // shift all digits left
			dot.value += tile - '0'; // tack on the new digit
			return true; // don't do any other processing for this tile
		}
		else
			dot.state = STATE_NONE;
	} // exactly the same but for ID not value. TODO: don't repeat code
	else if(dot.state == STATE_READID){
		if(tile >= '0' && tile <= '9'){
			dot.id *= 10;
			dot.id += tile - '0';
			return true;
		}
		else
			dot.state = STATE_NONE;
	}

	return false;
}

bool Circuit::process_writing(const char &tile, Dot &dot){
	// encounter the output char, prepare to write something
	if(dot.state == STATE_NONE){
		if(tile == '$'){
			dot.state = STATE_WRITE;
			return true;
		}
	}
	// last char was a $, if this is # or @ then output value or ID
	else if(dot.state == STATE_WRITE){
		if(tile == '#'){
			output(std::to_string(dot.value));
			return true;
		}
		else if(tile == '@'){
			output(std::to_string(dot.id));
			return true;
		}
		else{ // not a valid thing to output
			dot.state = STATE_NONE;
			return false;
		}
	}
	return false;
}