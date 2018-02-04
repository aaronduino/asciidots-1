#pragma once
#include <string>
#include <vector>

class Circuit{
public:
	// bounds
	uint32_t width, height;

	void load_circuit(const std::string &path);

	char get_tile(const uint32_t &y, const uint32_t &x);

private:
	// working section of the circuit
	std::vector<std::string> body;
};