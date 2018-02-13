#include "write.h"
#include "../dot.h"

Write::Write(const Vec2 &pos): Tile(pos){
  this->pos = pos;
}

void Write::add_dot(Dot *dot){
  dot->state = STATE_WRITE;
}