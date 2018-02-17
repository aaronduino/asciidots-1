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

  set_mode(MODE_DEBUG);

  if(get_mode() == MODE_DEBUG)
    Debug::init_debug();

  while(circuit.step()){ // loop until circuit reports stability
    if(get_mode() == MODE_DEBUG)
      Debug::draw(circuit); // draw circuit

    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // wait a bit
  }

  if(get_mode() == MODE_DEBUG)
    Debug::end_debug();

  return EXIT_SUCCESS;
}