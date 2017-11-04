#include <chrono>
#include <thread>
#include "interpret.h"
#include "circuittools.h"
#include "debug.h"
#include "stepper.h"

using namespace std;

Interpret::Interpret(string filename){
  circuit = LoadCircuit(filename);

  vector<Dot> dots = SpawnDots();

  Debug debug(circuit);
  Stepper stepper(circuit);

  debug.DrawDots(dots);

  while(true){
    this_thread::sleep_for(chrono::milliseconds(250));
    stepper.Step(dots);
    debug.DrawDots(dots);
  }
}

vector<string> Interpret::LoadCircuit(string filename){
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
  vector<string> out(height);

  file.clear();
  file.seekg(0, file.beg); // reset reader

  for(int i = 0; i < height; i++){
    getline(file, line);
    out[i] = line + string(width - line.length(), ' '); // pad to width
  }

  file.close();

  return out;
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
    vector<Point> escapes = FindEscapes(p, circuit);

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
