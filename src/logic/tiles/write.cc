#include "write.h"
#include "../dot.h"

Write::Write(const Vec2 &pos): Tile(pos) {}

void Write::add_dot(Dot *dot){
  dot->state = STATE_WRITE;
}

int Write::get_type(){
  return TILE_WRITE;
}