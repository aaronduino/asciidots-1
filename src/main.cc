#include <iostream> // cout, endl, EXIT_...
#include <thread> // sleep_for
#include <chrono> // seconds
#include "logic/circuit.h"
#include "io/debug.h"

int main(int argc, char **argv){
	if(argc != 2) return EXIT_FAILURE;

	Circuit circuit;
	circuit.load_circuit(argv[1]);

	// init new debugger
	Debug debug;

	// loop until circuit reports stability
	while(circuit.step()){
		debug.draw(circuit); // draw circuit

		// pause for a moment
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	return EXIT_SUCCESS;
}