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
		dots.push_back(Dot(Vec2(x, y), exits[0]));
}

char Circuit::get_tile(const uint32_t &y, const uint32_t &x){
	std::string row = body[y];

	// if out of bounds, return ' '
	if(x >= row.length() || y >= height)
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

bool Circuit::step(){
	if(dots.size() == 0)
		return false;

	for(uint32_t i = 0; i < dots.size(); i++){
		// move this dot
		dots[i].move();

		// what tile did it land on
		char tile = get_tile(dots[i].pos.y, dots[i].pos.x);

		// if we landed on empty or illegally entered a tile, die
		if(tile == ' ' || !valid_travel(tile, dots[i].dir)){
			dots.erase(dots.begin()+i);
			i--; // everything shifts down, so go back one
			continue;
		}

		// TILE PROCESSING
		process_flow(tile, dots[i]);
	}

	return true;
}