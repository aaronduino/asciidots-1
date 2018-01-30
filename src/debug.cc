#include "debug.h"
#include <iostream>

void draw_circuit(Circuit circuit){
	for(int y = 0; y < circuit.height; y++){
		for(int x = 0; x < circuit.width; x++){
			std::cout << circuit.get_tile(x, y);
		}
		std::cout << std::endl;
	}
}