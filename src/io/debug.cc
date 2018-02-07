#include "debug.h"
#include <ncurses.h>
#include "../logic/circuit.h"
#include "io.h"

Debug::Debug(){
	initscr();
	curs_set(0); // hide cursor

	// windows
	wcircuit = newwin(6, 25, 0, 0);
	woutput = newwin(5, 25, 6, 0);

	// colours
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK); // dots
}

Debug::~Debug(){
	curs_set(1); // bring cursor back
	endwin(); // clean up ncurses
}

void Debug::draw(Circuit circuit){
	draw_circuit(circuit); // base layer
	decorate_circuit(circuit); // colour

	// update circuit window
	wrefresh(wcircuit);

	draw_output();
	wrefresh(woutput);
}

void Debug::draw_circuit(Circuit circuit){
	// iterate all tiles
	for(uint32_t y = 0; y < circuit.height; y++){
		for(uint32_t x = 0; x < circuit.width; x++){
			// load tile, move and draw it
			char tile = circuit.get_tile(y, x);
			mvwaddch(wcircuit, y, x, tile);
		}
	}
}

void Debug::decorate_circuit(Circuit circuit){
	// iterate dots
	for(uint32_t i = 0; i < circuit.dots.size(); i++){
		int y, x; // pull dot's position for convenience
		y = circuit.dots[i].pos.y; x = circuit.dots[i].pos.x;

		char tile = circuit.get_tile(y, x); // find tile
		// replace the tile but with colour
		mvwaddch(wcircuit, y, x, tile | COLOR_PAIR(1));
	}
}

void Debug::draw_output(){
	for(uint32_t i = 0; i < get_output().size(); i++){
		mvwaddstr(woutput, i, 0, get_output()[i].c_str());
	}
}