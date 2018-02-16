#include <iostream> // cout, endl, EXIT_...
#include <thread> // sleep_for
#include <chrono> // seconds
#include "logic/circuit.h"
#include "io/debug.h"
#include "io/io.h"

int main(int argc, char **argv){
  if(argc != 2) return EXIT_FAILURE;

  Circuit circuit;
  circuit.load_circuit(argv[1]);

  Debug::init_debug();
  set_mode(MODE_DEBUG);

  while(circuit.step()){ // loop until circuit reports stability
    Debug::draw(circuit); // draw circuit

    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // wait a bit
  }

  Debug::end_debug();

  return EXIT_SUCCESS;
}