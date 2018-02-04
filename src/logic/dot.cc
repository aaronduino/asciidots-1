#include "dot.h"

Dot::Dot(Vec2 pos, Vec2 dir){
	this->pos = pos;
	this->dir = dir;
}

Dot::Dot(const Dot &dot){
	pos = dot.pos;
	dir = dot.dir;
	value = dot.value;
	id = dot.id;
}

void Dot::move(){
	pos += dir;
}

void Dot::turn(int turns){
	// get number of turns between 0 and 3
	turns %= 4;
	if(turns < 0) // make CCW turns CW
		turns += 4;

	switch(turns){
		default:
			break; // no turning needed
		case 1:
			dir.x ^= dir.y; dir.y ^= dir.x;	dir.x ^= dir.y; // XOR swap x and y
			dir.x *= -1; // flip the x
			break;
		case 2:
			dir.x *= -1; // flip x and y
			dir.y *= -1;
			break;
		case 3:
			dir.x ^= dir.y; dir.y ^= dir.x;	dir.x ^= dir.y; // XOR swap x and y
			dir.y *= -1; // flip the y
			break;
	}
}