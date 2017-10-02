#include "circuittools.h"
#include "tiletools.h"

bool CircuitTools::WithinBounds(Point p) // point inside circuit?
{
  if(p.x < 0 || p.x >= width)
    return false;
  if(p.y < 0 || p.y >= height)
    return false;

  return true;
}

// returns direction vectors a dot can point for a valid exit from tile at p
// verbose, I know
std::vector<Point> CircuitTools::FindEscapes(Point p)
{
  int map[] = { 0, 3, 1, 2 }; // maps vecDir order to clockDir values
  int order = 0; // easier to map order than value to a clockDir

  std::vector<Point> out;

  for(int y = -1; y <= 1; y++) for(int x = -1; x <= 1; x++)
  {
    Point o { x, y }; // offset
    Point q = p + o; // offset p by o

    // escapes
    if(!WithinBounds(q))
      continue; // certainly not

    if(!( (x == 0) ^ (y == 0) ))
      continue; // ONE and ONLY ONE offset must be 0

    if(TileTools::ValidEntry(circuit[q.y][q.x], map[order]))
      out.push_back(o); // valid vector, push to output

    order++; // next vector to be used
  }

  return out;
}
