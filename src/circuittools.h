#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "point.h"

// classless
bool WithinBounds(Point p, std::vector<std::string> circuit);
std::vector<Point> FindEscapes(Point p, std::vector<std::string> circuit);
