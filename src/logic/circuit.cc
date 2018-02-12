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

	// init body
	parse_body();
}

char Circuit::get_tile(const int64_t &y, const int64_t &x){
	std::string row = body[y];

	// if out of bounds, return ' '
	if(x >= (int64_t)row.length() || x < 0 || y >= (int64_t)height || y < 0)
		return ' ';
	else
		return row[x];
}

// assumes legal travel, returns false if illegal
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

void Circuit::spawn_dot(const uint32_t &y, const uint32_t &x){
	// find a direction for the dot to spawn pointing
	Vec2 compass[4] = { Vec2(0, -1), Vec2(1, 0), Vec2(0, 1), Vec2(-1, 0) };
	std::vector<Vec2> exits;
	for(int i = 0; i < 4; i++){
		// prevent underflow
		if((x == 0 && compass[i].x < 0) || (y == 0 && compass[i].y < 0))
			continue;

		char tile = get_tile(y + compass[i].y, x + compass[i].x);

		if(tile == ' ') // empty space isn't an exit
			continue;

		// only an exit if we can legally go this way
		if(valid_travel(tile, compass[i]))
			exits.push_back(compass[i]);
	}

	// only spawn if there's a possible unambiguous exit
	if(exits.size() == 1)
		dots.push_back(new Dot(Vec2(x, y), exits[0]));
}

void Circuit::parse_body(){
	
}