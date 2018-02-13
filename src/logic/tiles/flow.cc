#include "flow.h"
#include "../dot.h"

Flow::Flow(const Vec2 &pos, const char &tileChar) : Tile(pos){
  this->pos = pos;
  this->tileChar = tileChar;
}

void Flow::add_dot(Dot *dot){
  switch(tileChar){
    case '<':
      dot->dir = Vec2(-1, 0);
      break;
    case '>':
      dot->dir = Vec2(1, 0);
      break;
    case '^':
      dot->dir = Vec2(0, -1);
      break;
    case 'v':
      dot->dir = Vec2(0, 1);
      break;
    case '\\':
      if(dot->dir.y == 0) // if horizontal
          dot->turn(1);
        else
          dot->turn(-1);
      break;
    case '/':
      if(dot->dir.x == 0) // if vertical
          dot->turn(1);
        else
          dot->turn(-1);
      break;
    default:
      break;
  }
}