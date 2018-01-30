#include "circuit.h"
#include <fstream>
#include <iostream>

Circuit::Circuit(const std::string &path){
	std::ifstream file(path);
	std::string line;

	// bounding box dimensions
	int width = 0, height = 0;

	// pull each line into data
	while(std::getline(file, line)){
		data.push_back(line);

		// tick height, use widest line
		height++;
		if((int)line.length() > width)
			width = line.length();
	}

	this->width = width;
	this->height = height;
}