#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "point.h"

class CircuitTools{
public:
  // init the circuit we're using etc
  CircuitTools(std::string circuit[], int width, int height){
    this->circuit = circuit;

    this->width = width;
    this->height = height;
  }
  // should we need to construct without knowing bounds
  CircuitTools(std::string circuit[]){
    this->circuit = circuit;
    //std::cout << circuit[0][0] << "\n";

    this->width = circuit[0].size();
    this->height = circuit->size();
  }

  // check point inside circuit
  bool WithinBounds(Point p);

  // where can a dot escape to from point p in circuit
  std::vector<Point> FindEscapes(Point p);

private:
  std::string* circuit;

  int width, height;
};
