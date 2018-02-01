#include <ncurses.h>
#include "circuit.h"
#include "debug.h"

int main(int argc, char **argv){
	// start an ncurses screen
	initscr();

	// load circuit
	Circuit circuit(argv[1]);
	circuit.dots.push_back(Dot(Vec2(0, 0), Vec2(1, 0)));

	// draw circuit
	draw(circuit);

	// quit on keypress
	getch();

	// clean up window
	endwin();

	return 0;
}
