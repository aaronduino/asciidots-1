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
  std::vector<std::string> circuit;
  std::vector<Dot> cloneBuffer;

  void FlowCheck(Dot *dot, char tile);
  void CloneCheck(Dot *dot, char tile);
};
