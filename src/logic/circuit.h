#pragma once
#include <string>
#include <vector>

class Dot;
class Vec2;

class Circuit{
public:
	// bounds
	uint32_t width, height;

	// dot collection
	std::vector<Dot> dots;


	void load_circuit(const std::string &path);

	// scans body for things to initialise, calls appropriate handlers
	void parse_body();

	// attempt to spawn a dot here
	void spawn_dot(const uint32_t &y, const uint32_t &x);

	char get_tile(const int64_t &y, const int64_t &x);

	// can this tile legally be entered in this direction
	bool valid_travel(const char &tile, const Vec2 &dir);

	// PROCESSING
	// move and process all dots once, returns true if stuff happens
	bool step();

	// process direction of flow tiles
	void process_flow(const char &tile, Dot &dot);

private:
	// working section of the circuit
	std::vector<std::string> body;
};