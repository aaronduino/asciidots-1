#pragma once
#include <string>
#include <vector>
#include "dot.h"
#include "../vec2.h"
#include "tiles/tile.h"

class Circuit{
public:
  uint32_t width, height; // bounds in tiles

  std::vector<Dot*> dots; // dot collection
  std::vector<Tile*> tiles; // tiles that actually do things

  void load_circuit(const std::string &path); // load circuit from file
  char get_tile(const int32_t &y, const int32_t &x) const;
  bool step(); // move all dots, process all interesting tiles
  void collect_inputs();

private:
  std::vector<std::string> body; // payload of the circuit file

  bool valid_travel(const char &tile, const Vec2 &dir); // can enter tile in dir
  void spawn_dot(const uint32_t &y, const uint32_t &x);
  void parse_body(); // scan the body for interesting tiles, create objects
  void process_io(Dot *dot, const char &tile); // handle any reading/writing
  void post_step(); // handle business after every dot has stepped  
};