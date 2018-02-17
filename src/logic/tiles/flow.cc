#include "flow.h"
#include "../dot.h"

Flow::Flow(const Vec2 &pos, const char &tileChar) : Tile(pos){
  this->tileChar = tileChar;
}

void Flow::add_dot(Dot *dot){
  switch(tileChar){
    case '<':
      dot->dir = Vec2(-1, 0); // set left
      break;
    case '>':
      dot->dir = Vec2(1, 0); // set right
      break;
    case '^':
      dot->dir = Vec2(0, -1); // set up
      break;
    case 'v':
      dot->dir = Vec2(0, 1); // set down
      break;
    case '\\':
      if(dot->dir.y == 0) // if horizontal
        dot->turn(1); // turn CW
      else
        dot->turn(-1); // turn CCW
      break;
    case '/':
      if(dot->dir.x == 0) // if vertical
        dot->turn(1); // turn CW
      else
        dot->turn(-1); // turn CCW
      break;
    default:
      break;
  }
}

int Flow::get_type(){
  return TILE_FLOW;
}