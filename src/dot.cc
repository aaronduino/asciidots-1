#include "dot.h"

Dot::Dot(const Vec2 &pos, const Vec2 &dir){
	this->pos = pos;
	this->dir = dir;
}

void Dot::move(){
	pos += dir;
}