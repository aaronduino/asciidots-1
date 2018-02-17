#pragma once
#include "tile.h"

/* a tile that affects a dot's direction of travel
   tileChars include:     < > ^ v \ /               */
class Flow: public Tile{
public:
  Vec2 pos;
  
  Flow(const Vec2 &pos, const char &tileChar);

  void add_dot(Dot *dot);
  int get_type();

private:
  char tileChar; // this tile's flow character
};