#include "io.h"
#include <iostream>
#include "debug.h"

int mode; // io interface, either stdio or the debugger

int input(){
  if(mode == MODE_STDIO){
    std::string raw;
    getline(std::cin, raw);
    return stoi(raw);
  }
  else return 0;
}

void output(const std::string &text){
  if(mode == MODE_STDIO)
    std::cout << text << std::endl;
  else if(mode == MODE_DEBUG)
    Debug::output(text);    
}

void set_mode(const int &val){
  mode = val;
}
int get_mode(){
  return mode;
}