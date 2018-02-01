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


	// load a circuit from path into data
	Circuit(const std::string &path);

	// return a tile at x, y. if out of bounds, return whitespace
	char get_tile(const int &x, const int &y);

private:
	std::vector<std::string> data;
};