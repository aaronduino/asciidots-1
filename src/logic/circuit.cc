#include "circuit.h"
#include <fstream>
#include "dot.h"

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

	// init body
	parse_body();
}

void Circuit::parse_body(){
	// scan
	for(uint32_t y = 0; y < height; y++) for(uint32_t x = 0; x < width; x++){
		// dot spawn
		if(get_tile(y, x) == '.')
			spawn_dot(y, x);
	}
}

void Circuit::spawn_dot(const uint32_t &y, const uint32_t &x){
	// spawn
	dots.push_back(Dot(Vec2(x, y), Vec2(1, 0)));
}

char Circuit::get_tile(const uint32_t &y, const uint32_t &x){
	std::string row = body[y];

	if(x >= row.length())
		return ' ';
	else
		return row[x];
}

// assumes legal travel, false if illegal
bool Circuit::valid_travel(const char &tile, const Vec2 &dir){
	// moving vertical, entering a horizontal?
	if(dir.x == 0 && (tile == '-' || tile == '(' || tile == ')'))
			return false;
	// moving horizontal, entering a vertical?
	else if(dir.y == 0 && tile == '|')
		return false;
	else
		return true;
}
