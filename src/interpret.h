#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "dot.h"
#include "operator.h"

class Interpret{
public:
  Interpret(std::string filename);

private:
  std::vector<std::string> LoadCircuit(std::string filename);
  std::vector<Operator> LoadOperators(std::vector<std::string> circuit);
  std::vector<Dot> SpawnDots(std::vector<std::string> circuit);
};
