#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Interpret{
public:
  Interpret(string filename);
private:
  string* circuit;

  string* LoadCircuit(string filename);
};
