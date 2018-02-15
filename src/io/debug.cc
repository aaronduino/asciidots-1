#include "debug.h"
#include <ncurses.h>
#include <iostream>
#include "../logic/circuit.h"
#include "io.h"

// windows
WINDOW *wcircuit;
WINDOW *woutput;

void draw_circuit(const Circuit &circuit);
void decorate_circuit(const Circuit &circuit);
void draw_output();

void Debug::init_debug(){
  initscr();
  curs_set(0); // hide cursor

  int y, x;
  getmaxyx(stdscr, y, x);

  // windows
  wcircuit = newwin(y-10, x, 0, 0);
  woutput = newwin(9, x, y-9, 0);

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

  wrefresh(wcircuit); // update circuit window

  draw_output();

  wrefresh(woutput);

  move(wcircuit->_maxy+1, 0);
  hline('-', wcircuit->_maxx+1);
  refresh();
}

void draw_circuit(const Circuit &circuit){
  // iterate all tiles
  for(uint32_t y = 0; y < circuit.height; y++){
    for(uint32_t x = 0; x < circuit.width; x++){
      // load tile, move and draw it
      mvwaddch(wcircuit, y, x, circuit.get_tile(y, x));
    }
  }
}

void decorate_circuit(const Circuit &circuit){
  // iterate dots
  for(uint32_t i = 0; i < circuit.dots.size(); i++){
    int y, x; // pull dot's position for convenience
    y = circuit.dots[i]->pos.y; x = circuit.dots[i]->pos.x;

    // replace the tile but with colour
    mvwaddch(wcircuit, y, x, circuit.get_tile(y, x) | COLOR_PAIR(1));
  }
}

void draw_output(){
  // write in some lines from the output buffer
  for(uint32_t i = 0; i < get_output().size(); i++){
    mvwaddstr(woutput, i, 0, get_output()[i].c_str());
  }
}