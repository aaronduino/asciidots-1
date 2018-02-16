#pragma once

// forward dec
class Circuit;

namespace Debug{
  void init_debug();
  void end_debug();
  void draw(const Circuit &circuit); // draw all debug windows
}