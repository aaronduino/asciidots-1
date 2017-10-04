#include "interpret.h"
#include "circuittools.h"

using namespace std;

Interpret::Interpret(string filename){
  circuit = LoadCircuit(filename);

  CircuitTools circuitTools(circuit);
  cout << circuitTools.FindEscapes(Point{ 2, 0 }).size() << "\n";
}

string* Interpret::LoadCircuit(string filename){
  // get circuit's dimensions
  uint width, height = 0;

  string line;
  ifstream file(filename);

  while(getline(file, line)){
    height++;

    if(line.length() > width) // new longest line
      width = line.length();
  }

  // pull lines to memory
  string* circuit = new string[height];

  file.clear();
  file.seekg(0, file.beg); // reset reader
  
  for(int i = 0; i < height; i++){
    getline(file, line);
    circuit[i] = line + string(width - line.length(), ' '); // pad to width
  }

  file.close();

  return circuit;
}
