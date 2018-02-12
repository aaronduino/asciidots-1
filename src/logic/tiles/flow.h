#pragma once
#include "tile.h"
//#include "../../vec2.h"

// a tile that affects a dot's direction of travel
// tileChars include: < > ^ v \ /
class Flow: public Tile{
public:
	Vec2 pos;
	// lots of flow characters, keeps track of this one's
	char tileChar;

	Flow(const Vec2 &pos, const char &tileChar);

	void add_tile(Dot *dot);
};