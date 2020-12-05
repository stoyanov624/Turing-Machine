#include <iostream>
#include "TuringMachine.h"


int main()
{
	Tape tape("11111111");
	tape.move_right();
	tape.move_right();
	tape.move_right();
	tape.move_right();
	

	std::map<std::string, std::vector<Transition*>> instructions;
	instructions["start"].push_back(new Transition("q1", '1', '0', 'L', "q2"));
	instructions["start"].push_back(new Transition("halt", '0', '0', ' ', ""));
	instructions["q1"].push_back(new Transition("q1", '1', '0', 'L', "q1"));
	instructions["q1"].push_back(new Transition("q2", '0', '1', ' ', "start"));
	instructions["q2"].push_back(new Transition("start", '0', '0', 'L', "halt"));
	instructions["q2"].push_back(new Transition("start", '1', '1', 'R', "halt"));

	
	TuringMachine turing_m(&tape,instructions);
	turing_m.runMachine();
}
