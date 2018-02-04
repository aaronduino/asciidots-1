#include "dot.h"

Dot::Dot(Vec2 pos, Vec2 dir){
	this->pos = pos;
	this->dir = dir;
}

void Dot::move(){
	pos += dir;
}