#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "dot.h"
#include "operator.h"

class Stepper{
public:
  Stepper(std::vector<std::string> circuit, std::vector<Operator> ops);

  void Step(std::vector<Dot> &dots);

private:
  std::vector<std::string> circuit;
  std::vector<Operator> ops;

  std::vector<Dot> cloneBuffer;

  void FlowCheck(Dot &dot, char tile);
  void CloneCheck(Dot dot, char tile);
  void OperatorCheck(Dot &dot);
};
