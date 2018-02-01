#include "debug.h"
#include <ncurses.h>

void draw(Circuit circuit){
	draw_circuit(circuit);
	draw_dots(circuit);
	// update for changes
	refresh();	
}

void draw_circuit(Circuit circuit){
	for(int y = 0; y < circuit.height; y++){
		for(int x = 0; x < circuit.width; x++){
			move(y, x);
			addch(circuit.get_tile(x, y));
		}
	}
}

void draw_dots(Circuit circuit){
	// go red
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	attron(COLOR_PAIR(1));

	for(int i = 0; i < (int)circuit.dots.size(); i++){
		int x = circuit.dots[i].pos.x;
		int y = circuit.dots[i].pos.y;
		move(y, x);
		addch(circuit.get_tile(x, y));
	}
	// turn off red
	attroff(COLOR_PAIR(1));
}