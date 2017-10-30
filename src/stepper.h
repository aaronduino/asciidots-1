#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "dot.h"

class Stepper{
public:
  Stepper(std::vector<std::string> circuit);

  void Step(std::vector<Dot> *dots);

private:
  std::shared_ptr<std::vector<Dot>> dots; // hold dots with unique IDs
  std::vector<std::string> circuit;
};
