#include "io.h"
#include "debug.h"

int mode; // io interface, either stdio or the debugger

void output(const std::string &text){
  if(mode == MODE_DEBUG)
    Debug::output(text);    
}

void set_mode(const int &val){
  mode = val;
}