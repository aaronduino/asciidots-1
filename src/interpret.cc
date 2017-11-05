#include <chrono>
#include <thread>
#include "interpret.h"
#include "circuittools.h"
#include "debug.h"
#include "stepper.h"

using namespace std;

Interpret::Interpret(string filename){
  vector<string> circuit = LoadCircuit(filename);
  vector<Operator> ops = LoadOperators(circuit);
  vector<Dot> dots = SpawnDots(circuit);

  Debug debug(circuit);
  Stepper stepper(circuit, ops);

  debug.DrawDots(dots);

  while(true){
    this_thread::sleep_for(chrono::milliseconds(250));
    stepper.Step(dots);
    debug.DrawDots(dots);
  }
}

vector<string> Interpret::LoadCircuit(string filename){
  // get circuit's dimensions
  int width, height;
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

vector<Operator> Interpret::LoadOperators(vector<string> circuit){
  int height = circuit.size();
  int width = circuit[0].length();

  vector<Operator> out;
  // valid opening bracket can't possibly be within last two chars
  for(int y = 0; y < height; y++) for(int x = 0; x < width-2; x++){
    bool horizontal;
    if(circuit[y][x] == '{' && circuit[y][x+2] == '}')
      horizontal = true;
    else if(circuit[y][x] == '[' && circuit[y][x+2] == ']')
      horizontal = false;
    else
      continue; // this isn't a valid opening operator, skip

    //Operator op(Point { x+1, y }, circuit[y][x+1], horizontal))
    out.push_back(Operator(Point { x+1, y }, circuit[y][x+1], horizontal));
  }
  return out;
}

// find spawns, return prepared dots. obviously load circuit first
vector<Dot> Interpret::SpawnDots(vector<string> circuit){
  int height = circuit.size();
  int width = circuit[0].length();

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
