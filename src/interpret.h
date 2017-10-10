#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "dot.h"

class Interpret{
public:
  Interpret(std::string filename);

private:
  uint width, height; // circuit dimensions
  int dotCounter = 0; // counts IDs

  std::vector<std::string> circuit;

  std::vector<std::string> LoadCircuit(std::string filename);
  std::vector<Dot> SpawnDots();
};
