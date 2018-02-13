#include "io.h"

std::vector<std::string> outputBuffer;

void output(const std::string &text){
  outputBuffer.push_back(text);
}

std::vector<std::string> get_output(){
  return outputBuffer;
}