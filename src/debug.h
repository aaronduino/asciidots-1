#pragma once
#include <iostream>
#include <curses.h>
#include <string>
#include <vector>
#include "dot.h"

class Debug{
public:
  Debug(std::vector<std::string> circuit);

  void DrawDots(std::vector<Dot>); // colours tiles with dots

private:
  std::vector<std::string> circuit;
  std::vector<std::vector<int>> colourMap; // stores tile colour codes
  std::vector<Dot> prevDots; // state of the last call's dots

  void DrawCircuit(); // draws the uncoloured base
};
