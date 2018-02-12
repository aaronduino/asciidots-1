#pragma once
#include <string>
#include <vector>
#include "dot.h"
#include "../vec2.h"
#include "tiles/tile.h"

// implementation split between circuit.cc and processing.cc
class Circuit{
public:
	// bounds
	uint32_t width, height;

	// dot collection
	std::vector<Dot*> dots;

	// collection of active tile objects
	std::vector<Tile*> tiles;


	// loads circuit from file into body
	void load_circuit(const std::string &path);

	// returns a tile char, if out of bounds returns whitespace
	char get_tile(const int64_t &y, const int64_t &x);	

	// can this tile legally be entered in this direction
	bool valid_travel(const char &tile, const Vec2 &dir);

	// attempt to spawn a dot here
	void spawn_dot(const uint32_t &y, const uint32_t &x);

		// scans body for things to initialise, calls appropriate handlers
	void parse_body();

	// move and process all dots once, returns true if stuff happens
	bool step();

private:
	// working section of the circuit
	std::vector<std::string> body;
};