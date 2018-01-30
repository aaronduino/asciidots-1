#pragma once
#include <string>
#include <vector>

class Circuit{
public:
	// load a circuit from path into data
	Circuit(const std::string &path);

private:
	std::vector<std::string> data;

	int width, height;
};