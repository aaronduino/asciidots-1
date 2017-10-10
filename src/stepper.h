#include <iostream>
#include <vector>
#include "dot.h"

class Stepper{
public:
  Stepper(std::vector<Dot> dots);

private:
  std::vector<Dot> dots; // hold dots with unique IDs
};
