#pragma once

class Circuit;

// start and clean up the ncurses env
void init_debug();
void end_debug();

void draw_circuit(Circuit circuit);