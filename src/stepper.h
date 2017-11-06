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

  std::vector<std::string> Step(std::vector<Dot> &dots);

private:
  std::vector<std::string> circuit;
  std::vector<Operator> ops;

  std::vector<Dot> cloneBuffer;

  void FlowCheck(Dot &dot, char tile);
  void CloneCheck(Dot dot, char tile);
  void OperatorCheck(Dot &dot);
  void ReadCheck(Dot &dot, char tile);
  std::vector<std::string> WriteCheck(Dot &dot, char tile);
};
