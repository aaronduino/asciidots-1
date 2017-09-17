#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class interpret{
public:
  interpret(string filename);
private:
  string* circuit;

  string* LoadCircuit(string filename);
};
