#include <iostream>
#include "TuringMachine.h"


int main()
{
	Tape tape("11111111");
	tape.move_right();
	tape.move_right();
	tape.move_right();
	tape.move_right();

	std::map<std::string, std::vector<Transition>> instructions;
	instructions["start"].push_back(Transition("q1", '1', '0', 'L'));
	instructions["start"].push_back(Transition("halt", '0', '0', ' '));
	instructions["q1"].push_back(Transition("q1", '1', '0', 'L'));
	instructions["q1"].push_back(Transition("q2", '0', '1', ' '));
	instructions["q2"].push_back(Transition("start", '0', '0', 'L'));
	instructions["q2"].push_back(Transition("start", '1', '1', 'R'));


	TuringMachine turing_m(tape, instructions);
	//turing_m.runMachine();
	turing_m.printTape();

	//TuringMachine tm;
	//std::ifstream inFile("machine.txt");
	//tm.loadMachine(inFile);
	
}
