#pragma once

// forward decs
class Circuit;
typedef struct _win_st WINDOW;

class Debug{
public:
  Debug();
  ~Debug();

  void draw(Circuit circuit); // draw all debug windows

private:
  // windows
  WINDOW *wcircuit;
  WINDOW *woutput;

  void draw_circuit(Circuit circuit); // draw the circuit (no colour)
  void decorate_circuit(Circuit circuit); // colour interesting features  
  void draw_output(); // draw the output window
};