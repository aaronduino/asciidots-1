#include "circuit.h"
#include <fstream>

Circuit::Circuit(const std::string &path){
	std::ifstream file(path);
	std::string line;

	// reset bounding box
	width = height = 0;

	// pull each line into data
	while(std::getline(file, line)){
		data.push_back(line);

		// tick height, use widest line
		height++;
		if((int)line.length() > width)
			width = line.length();
	}
}

char Circuit::get_tile(const int &x, const int &y){
	// out of bounds, return whitespace
	if(x < 0 || x >= width || y < 0 || y >= height)
		return ' ';

	return data[y][x];
}