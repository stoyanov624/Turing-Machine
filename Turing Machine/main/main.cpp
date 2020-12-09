#include <iostream>
#include "TuringMachine.h"


int main()
{

	TuringMachine tm;
	Tape tape("0110110");
	tm.addTape(tape);
	tm.addTransition("start", Transition("q1", '0', '1', 'R'));
	tm.addTransition("start", Transition("q1", '1', '1', 'R'));
	tm.addTransition("q1", Transition("q1", '0', '1', 'R'));
	tm.addTransition("q1", Transition("q1", '1', '1', 'R'));
	tm.addTransition("q1", Transition("halt", '_', '_', 'L'));

	//tm.runMachine();

	TuringMachine tm2;
	Tape tape2("0110110");
	tm2.addTape(tape2);
	tm2.addTransition("start", Transition("reject", '0', '0', 'H'));
	tm2.addTransition("start", Transition("q2", '1', '1', 'R'));
	tm2.addTransition("q2", Transition("start", '1', '0', 'R'));
	tm2.addTransition("q2", Transition("reject", '0', '0', ' '));
	tm2.addTransition("q2",Transition("halt",'_','_','L'));


	tm.composition(tm2);
}
