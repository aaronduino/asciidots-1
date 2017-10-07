#include "interpret.h"
#include "circuittools.h"

using namespace std;

Interpret::Interpret(string filename){
  circuit = LoadCircuit(filename);

  cout << SpawnDots().size() << "\n";
}

string* Interpret::LoadCircuit(string filename){
  // get circuit's dimensions
  width = height = 0;

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

// find spawns, return prepared dots. obviously load circuit first
vector<Dot> Interpret::SpawnDots(){
  vector<Dot> out;

  // look for spawn chars in circuit
  for(int y = 0; y < height; y++) for(int x = 0; x < width; x++){
    char tile  = circuit[y][x];

    if(tile != '.') // not what we're looking for
      continue;

    // didn't esc, this could be a spawn

    Point p { x, y };
    vector<Point> escapes = CircuitTools::FindEscapes(p, circuit);

    switch(escapes.size()){
      case 0:
        // spawned dot is doomed TODO: log warn about dead spawn
        break;
      case 1:{
        // unambiguous exit, spawn dot
        Dot dot(p, escapes[0]);
        out.push_back(dot);

        break;
      }
      default:
        // ambiguous exit dir TODO: log warn about unresolvable spawn
        break;
    }
  }

  return out;
}
