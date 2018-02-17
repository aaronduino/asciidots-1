#include "read.h"
#include "../dot.h"

Read::Read(const Vec2 &pos, const char &readType): Tile(pos){
  this->readType = readType;
}

void Read::add_dot(Dot *dot){
  if(dot->state == STATE_NONE){ // dots must be in default state to start a read
    if(readType == '#')
      dot->state = STATE_HASH;
    else if(readType == '@')
      dot->state = STATE_AT;
  }
}

int Read::get_type(){
  return TILE_READ;
}