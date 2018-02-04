#include "circuit.h"
#include <fstream>

void Circuit::load_circuit(const std::string &path){
	// clear body
	body = std::vector<std::string>();

	std::ifstream file(path);
	std::string line;
	
	width = height = 0;

	while(getline(file, line)){
		body.push_back(line);

		// increase bounds
		height++;
		if(line.length() > width) // use widest
			width = line.length();
	}

	file.close();
}

char Circuit::get_tile(const uint32_t &y, const uint32_t &x){
	std::string row = body[y];

	if(x >= row.length())
		return ' ';
	else
		return row[x];
}