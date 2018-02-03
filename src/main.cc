#include <iostream>
#include "logic/circuit.h"

int main(int argc, char **argv){
	if(argc != 2) return EXIT_FAILURE;

	Circuit circuit;
	circuit.load_circuit(argv[1]);

	return EXIT_SUCCESS;
}