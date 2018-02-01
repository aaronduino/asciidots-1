#pragma once
#include <string>
#include <vector>
#include "dot.h"

class Circuit{
public:
	// bounds of the circuit
	int width, height;

	// dot collection
	std::vector<Dot> dots;

	Circuit(const std::string &path);
	

	// load a circuit from path into data
	void load_circuit(const std::string &path);

	// return a tile at x, y. if out of bounds, return whitespace
	char get_tile(const int &x, const int &y);

	// find all spawn characters and add dots
	void spawn_dots();

private:
	std::vector<std::string> data;
};