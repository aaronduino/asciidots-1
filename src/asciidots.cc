#include <curses.h>
#include "interpret.h"

int main(int argc, char* argv[]){
  Interpret interpret(argv[1]);

  endwin();
}
