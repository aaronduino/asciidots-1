#pragma once
#include <iostream>
#include <fstream>
#include <string>

class Interpret{
public:
  Interpret(std::string filename);

private:
  std::string* circuit;

  std::string* LoadCircuit(std::string filename);
};
