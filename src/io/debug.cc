#include "debug.h"
#include <ncurses.h>
#include "../logic/circuit.h"
#include "../logic/dot.h"

void init_debug(){
	initscr();

	// colour pairs
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK); // dot
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

void draw_dots(Circuit circuit){
	attron(COLOR_PAIR(1));

	for(uint32_t i = 0; i < circuit.dots.size(); i++){
		Vec2 pos = circuit.dots[i].pos;
		move(pos.y, pos.x);
		addch(circuit.get_tile(pos.y, pos.x));
	}

	refresh();
	attroff(COLOR_PAIR(1));
}