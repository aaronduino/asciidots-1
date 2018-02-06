#pragma once

// forward declaration
class Circuit;
typedef struct _win_st WINDOW;

class Debug{
public:
	Debug();
	~Debug();

	// draw all debug windows
	void draw(Circuit circuit);

private:
	// windows
	WINDOW *wcircuit;

	// draw the circuit in white
	void draw_circuit(Circuit circuit);
	// colour interesting features
	void decorate_circuit(Circuit circuit);
};