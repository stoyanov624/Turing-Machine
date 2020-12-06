#include <iostream>
#include "TuringMachine.h"


int main()
{
	Tape tape("11111111");
	tape.move_right();
	tape.move_right();
	tape.move_right();
	tape.move_right();

	TuringMachine turing_m;
	turing_m.addTape(&tape);

	std::ifstream fileIn("instructions.txt");

	turing_m.loadInstructions(fileIn);
	turing_m.runMachine();
}
