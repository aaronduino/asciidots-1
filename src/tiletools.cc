#include "tiletools.h"

using namespace std;

// can a dot enter this tile in this direction
bool ValidEntry(char tile, int direction){
  /* defines the directions a dot can point in while entering a tile
  * from least to most significant, each bit represents up, right, left, down
  * NOTE: direction dot may point to enter, NOT the side they enter from
  * if a tile is not mapped, assume 0b1111
  */
  map<char, short> tileDirs{
    { '-', 0b1010 }, // horizontal
    { '|', 0b0101 }, // vertical
    //{ ')', 0b0010 }, // right
    //{ '(', 0b1000 }, // left
    { ' ', 0b0000 }  // space doesn't like anyone
  };

  // tile has no special rules?
  if(tileDirs.find(tile) == tileDirs.end()){ // no entry, assume valid
    return true;
  }
  else{
    int filter = tileDirs[tile];
    int sd = 1 << direction; // shift 1 to align with filter
    return (sd & filter) == sd; // sd passes through filter intact?
  }
}
