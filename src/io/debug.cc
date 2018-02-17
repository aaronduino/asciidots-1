#include "debug.h"
#include <ncurses.h>
#include <iostream>
#include <vector>
#include "../logic/circuit.h"

// windows
WINDOW *wcircuit;
WINDOW *woutput;
WINDOW *winput;

std::vector<std::string> outputBuffer;

void draw_circuit(const Circuit&);
void decorate_circuit(const Circuit&);
void draw_output();
void outline_window(WINDOW*, const std::string&); // outline and title a window

void Debug::init_debug(){
  initscr();
  curs_set(0); // hide cursor

  uint32_t outputLines = 5;

  int tHeight, tWidth; // total bounds
  getmaxyx(stdscr, tHeight, tWidth);

  int iHeight = 1; // input window height
  int oHeight = outputLines + 2; // output window height
  int cHeight = tHeight - oHeight - iHeight;

  // windows
  wcircuit = newwin(cHeight, tWidth, 0, 0);
  woutput = newwin(oHeight, tWidth, cHeight, 0);
  winput = newwin(iHeight, tWidth, cHeight + oHeight, 0);

  // colours
  start_color();
  init_pair(1, COLOR_RED, COLOR_BLACK); // dots
  init_pair(2, COLOR_CYAN, COLOR_BLACK); // ops, branches
  init_pair(3, COLOR_MAGENTA, COLOR_BLACK); // *
  init_pair(4, COLOR_BLUE, COLOR_BLACK); // #, @, $
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

int Debug::input(){
  mvwaddstr(winput, 0, 0, "?> ");
  char* raw = new char;
  wgetstr(winput, raw);
  return atoi(raw);
}
void Debug::output(const std::string &text){
  outputBuffer.push_back(text);
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
  // colour special tiles
  for(uint32_t i = 0; i < circuit.tiles.size(); i++){
    int y, x;
    y = circuit.tiles[i]->pos.y; x = circuit.tiles[i]->pos.x;

    switch(circuit.tiles[i]->get_type()){
      case TILE_BRANCH:
        mvwaddch(wcircuit, y+1, x+1, circuit.get_tile(y, x) | COLOR_PAIR(2));
        break;
      case TILE_CLONE:
        mvwaddch(wcircuit, y+1, x+1, circuit.get_tile(y, x) | COLOR_PAIR(3));      
        break;
      case TILE_OPERATOR:
        mvwaddch(wcircuit, y+1, x+1, circuit.get_tile(y, x) | COLOR_PAIR(2));        
        break;
      case TILE_READ:
        mvwaddch(wcircuit, y+1, x+1, circuit.get_tile(y, x) | COLOR_PAIR(4));      
        break;
      case TILE_WRITE:
        mvwaddch(wcircuit, y+1, x+1, circuit.get_tile(y, x) | COLOR_PAIR(4));      
        break;
    }
  }

  // highlight dots
  wattr_on(wcircuit, COLOR_PAIR(1) | A_BOLD, 0);

  for(uint32_t i = 0; i < circuit.dots.size(); i++){
    int y, x; // pull dot's position for convenience
    y = circuit.dots[i]->pos.y; x = circuit.dots[i]->pos.x;

    // replace the tile but with colour
    mvwaddch(wcircuit, y+1, x+1, circuit.get_tile(y, x));
  }

  wattrset(wcircuit, A_NORMAL);
}

void draw_output(){
  // write in some lines from the output buffer
  for(uint32_t i = 0; i < outputBuffer.size(); i++){
    mvwaddstr(woutput, i+1, 1, outputBuffer[i].c_str());
  }
}

void outline_window(WINDOW* window, const std::string& title){
  wborder(window, 0,0,0,0,0,0,0,0);
  mvwaddstr(window, 0, 2, title.c_str());
}