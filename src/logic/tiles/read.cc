#include "read.h"
#include "../dot.h"

Read::Read(const Vec2 &pos, const char &readType): Tile(pos){
  this->pos = pos;
  this->readType = readType;
}

void Read::add_dot(Dot *dot){
  // must be in neutral to begin reading
  if(dot->state == STATE_NONE){
    if(readType == '#')
      dot->state = STATE_HASH;
    else if(readType == '@')
      dot->state = STATE_AT;
  }
}