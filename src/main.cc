#include "circuit.h"
#include "debug.h"


int main(int argc, char **argv){
	Circuit circuit(argv[1]);
	draw_circuit(circuit);

	return 0;
}
