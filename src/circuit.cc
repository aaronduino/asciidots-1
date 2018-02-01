#include "circuit.h"
#include <fstream>

Circuit::Circuit(const std::string &path){
	load_circuit(path);
	spawn_dots();
}

void Circuit::load_circuit(const std::string &path){
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
	if(x < 0 || x >= (int)data[y].length() || y < 0 || y >= height)
		return ' ';

	return data[y][x];
}

void Circuit::spawn_dots(){
	// scan the circuit for '.' chars. TODO: support '·' (bullet)
	for(int y = 0; y < height; y++) for(int x = 0; x < width; x++){
		char tile = get_tile(x, y);

		if(tile == '.')
			dots.push_back(Dot(Vec2(x, y), Vec2(1, 0))); // face right for now
	}
}