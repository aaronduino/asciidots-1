#include <iostream> // cout, endl, EXIT_...
#include <thread> // sleep_for
#include <chrono> // seconds
#include "logic/circuit.h"
#include "io/debug.h"
#include "logic/dot.h"

int main(int argc, char **argv){
	if(argc != 2) return EXIT_FAILURE;

	Circuit circuit;
	circuit.load_circuit(argv[1]);

	init_debug();
	while(circuit.step()){
		draw_circuit(circuit);
		draw_dots(circuit);

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	end_debug();

	return EXIT_SUCCESS;
}