#include "clone.h"
#include "../dot.h"

Clone::Clone(const Vec2 &pos): Tile(pos) {}

void Clone::add_dot(Dot *dot){
  dot->state = STATE_CLONE; // let stepper do the actual cloning
}

int Clone::get_type(){
  return TILE_CLONE;
}