#include "dot.h"

Dot::Dot(Point position, int direction, int ID){
  this->position = position;
  this->PointTo(direction);
  this->ID = ID;
}
Dot::Dot(Point position, Point vDir, int ID){
  this->position = position;
  this->PointTo(vDir);
  this->ID = ID;
}

void Dot::PointTo(int direction){
  this->direction = direction & 3; // normalise 0->3

  switch(this->direction){ // set vDir
    case 0:
      vDir.x = 0; vDir.y = -1;
      break;
    case 1:
      vDir.x = 1; vDir.y = 0;
      break;
    case 2:
      vDir.x = 0; vDir.y = 1;
      break;
    case 3:
      vDir.x = -1; vDir.y = 0;
      break;
  }
}

void Dot::PointTo(Point vDir){
  this->vDir = vDir;

  switch(vDir.x){ // set clock
    case 0: // middle
      if(vDir.y == -1) // up
        direction = 0;
      else // down
        direction = 2;
      break;
    case -1: // left
      direction = 3;
      break;
    case 1: // right
      direction = 1;
      break;
  }
}

void Dot::Turn(int turns){ // clockwise quarter turns
  this->PointTo(direction + turns);
}
