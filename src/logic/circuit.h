#pragma once
#include <string>
#include <vector>

class Circuit{
public:
	// bounds
	uint32_t width, height;

	void load_circuit(const std::string &path);

private:
	// working section of the circuit
	std::vector<std::string> body;
};