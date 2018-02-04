#include <iostream>
#include "logic/circuit.h"
#include "io/debug.h"

int main(int argc, char **argv){
	if(argc != 2) return EXIT_FAILURE;

	Circuit circuit;
	circuit.load_circuit(argv[1]);

	init_debug();
	draw_circuit(circuit);
	end_debug();

	return EXIT_SUCCESS;
}