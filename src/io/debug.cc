#include "debug.h"
#include <ncurses.h>
#include <iostream>
#include "../logic/circuit.h"
#include "io.h"

// windows
WINDOW *wcircuit;
WINDOW *woutput;

void draw_circuit(const Circuit&);
void decorate_circuit(const Circuit&);
void draw_output();
void outline_window(WINDOW*, const std::string&); // outline and title a window

void Debug::init_debug(){
  initscr();
  curs_set(0); // hide cursor

  uint32_t outputLines = 5;

  int height, width; // stdscr bounds
  getmaxyx(stdscr, height, width);

  // windows
  wcircuit = newwin(height - outputLines - 2, width, 0, 0);
  woutput = newwin(outputLines+2, width, height - outputLines - 2, 0);

  // colours
  start_color();
  init_pair(1, COLOR_RED, COLOR_BLACK); // dots
}

void Debug::end_debug(){
  curs_set(1); // bring cursor back
  endwin(); // clean up ncurses
}

void Debug::draw(const Circuit &circuit){
  draw_circuit(circuit); // base layer
  decorate_circuit(circuit); // colour
  outline_window(wcircuit, "circuit");
  wrefresh(wcircuit); // update circuit window 

  draw_output();
  outline_window(woutput, "output");
  wrefresh(woutput);
}

void draw_circuit(const Circuit &circuit){
  // iterate all tiles
  for(uint32_t y = 0; y < circuit.height; y++){
    for(uint32_t x = 0; x < circuit.width; x++){
      // load tile, move and draw it
      mvwaddch(wcircuit, y+1, x+1, circuit.get_tile(y, x));
    }
  }
}

void decorate_circuit(const Circuit &circuit){
  // iterate dots
  for(uint32_t i = 0; i < circuit.dots.size(); i++){
    int y, x; // pull dot's position for convenience
    y = circuit.dots[i]->pos.y; x = circuit.dots[i]->pos.x;

    // replace the tile but with colour
    mvwaddch(wcircuit, y+1, x+1, circuit.get_tile(y, x) | COLOR_PAIR(1));
  }
}

void draw_output(){
  // write in some lines from the output buffer
  for(uint32_t i = 0; i < get_output().size(); i++){
    mvwaddstr(woutput, i+1, 1, get_output()[i].c_str());
  }
}

void outline_window(WINDOW* window, const std::string& title){
  wborder(window, 0,0,0,0,0,0,0,0);
  mvwaddstr(window, 0, 2, title.c_str());
}