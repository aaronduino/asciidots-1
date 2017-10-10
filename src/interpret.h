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
  int dotCounter = 0; // counts IDs

  int width, height; // circuit dimensions
  std::vector<std::string> circuit;

  std::vector<std::string> LoadCircuit(std::string filename);
  std::vector<Dot> SpawnDots();
};
