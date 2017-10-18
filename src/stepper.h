#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "dot.h"

class Stepper{
public:
  Stepper(std::vector<std::string> circuit, std::vector<Dot> dots);

private:
  std::vector<Dot> dots; // hold dots with unique IDs
  std::vector<std::string> circuit;

  void Step();
};
