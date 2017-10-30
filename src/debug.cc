#include "debug.h"

using namespace std;

Debug::Debug(vector<string> circuit){
  this->circuit = circuit;

  initscr();
  start_color();
  curs_set(0); // hide cursor

  init_pair(2, COLOR_BLUE, COLOR_BLACK);
  init_pair(1, COLOR_RED, COLOR_BLACK); // dot here colour

  this->DrawCircuit();
}

// colour tiles containing dots
void Debug::DrawDots(vector<Dot> dots){
  Point pos;
  for(int i = 0; i < prevDots.size(); i++){
    pos = prevDots[i].position;

    attron(COLOR_PAIR(colourMap[pos.y][pos.x]));
    move(pos.y, pos.x);
    addch(circuit[pos.y][pos.x]);
    attroff(COLOR_PAIR(colourMap[pos.y][pos.x]));
  }
  refresh();

  // colour this tick's dots
  for(int i = 0; i < dots.size(); i++){
    pos = dots[i].position; // convenience

    attron(COLOR_PAIR(1));
    move(pos.y, pos.x);
    addch(circuit[pos.y][pos.x]);
    attroff(COLOR_PAIR(1));
  }

  refresh();
  prevDots = dots; // remember these positions for next call
}

// draw the circuit "base", just white characters
void Debug::DrawCircuit(){
  int width = circuit[0].length();
  int height = circuit.size();

  colourMap.reserve(height);

  // line by line, char by char
  for(int y = 0; y < height; y++){
    vector<int> row(width); // for colour map

    for(int x = 0; x < width; x++){
      move(y, x);
      addch(circuit[y][x]);

      row.push_back(2); // blank colour
    }
    colourMap.push_back(row);
  }
  refresh();
}
