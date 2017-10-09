#include "debug.h"

using namespace std;

Debug::Debug(vector<string> circuit){
  width = circuit[0].length();
  height = circuit.size();

  this->circuit = circuit;

  initscr();
  this->DrawCircuit();
}

void Debug::DrawCircuit(){
  for(int y = 0; y < height; y++) for(int x = 0; x < width; x++){
    move(y, x);
    addch(circuit[y][x]);
  }
  refresh();
}
