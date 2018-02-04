#include "debug.h"
#include <ncurses.h>
#include "../logic/circuit.h"

void init_debug(){
	initscr();
}
void end_debug(){
	getch();
	endwin();
}

void draw_circuit(Circuit circuit){
	for(uint32_t y = 0; y < circuit.height; y++){
		for(uint32_t x = 0; x < circuit.width; x++){
			move(y, x);
			addch(circuit.get_tile(y, x));
		}
	}
	refresh();
}