#pragma once
#include <iostream>
#include <curses.h>
#include <string>
#include <vector>

class Debug{
public:
  Debug(std::vector<std::string> circuit);

private:
  int width, height;
  std::vector<std::string> circuit;

  void DrawCircuit(); // draws the uncoloured base
};
