#include <iostream>
#include "TuringMachine.h"
#include "LinearComposedTM.h"
#include "DeciderTM.h"
#include "WhileComposedTM.h"
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

TEST_CASE("testing tape movement,reading and writing") {
	//Tape t("123456");
	//CHECK(t.read() == '1');
	//t.move_right();
	//CHECK(t.read() == '2');
	//t.write('9');
	//CHECK(t.read() == '9');
	//t.show_tape();
}

TEST_CASE("testing tape infinity") {
	//Tape t("XXXXXX");
	//t.move_left();
	//CHECK(t.read() == '_');
	//t.move_right();
	//CHECK(t.read() == 'X');
	//t.show_tape();
}

TEST_CASE("testing machine that makes everything into 1") {
	//std::cout << "\nTESTING MACHINE!\n";
	//TuringMachine tm;
	//Tape tape("0110110");
	//tm.addTape(tape);
	//tm.addTransition("start", Transition("q1", '0', '1', 'R'));
	//tm.addTransition("start", Transition("q1", '1', '1', 'R'));
	//tm.addTransition("q1", Transition("q1", '0', '1', 'R'));
	//tm.addTransition("q1", Transition("q1", '1', '1', 'R'));
	//tm.addTransition("q1", Transition("halt", '_', '_', 'L'));

	//tm.runMachine();
	//std::cout << "\nTESTING DONE!\n";

}



TEST_CASE("testing decider machine") {
	//Tape t1("011011");
	//TuringMachine decider;
	//decider.setTape(t1);
	//decider.addTransition("start", Transition("reject", '_', '_', 'H'));
	//decider.addTransition("start", Transition("q1", '1', '1', 'R'));
	//decider.addTransition("start", Transition("q1", '0', '0', 'R'));
	//decider.addTransition("q1", Transition("q1", '1', '1', 'R'));
	//decider.addTransition("q1", Transition("q1", '0', '0', 'R'));
	//decider.addTransition("q1", Transition("q2", '_', '_', 'L'));
	//decider.addTransition("q2", Transition("reject", '0', '0', 'H'));
	//decider.addTransition("q2", Transition("accept", '1', '1', 'H'));


	//TuringMachine tm1;
	//tm1.addTransition("start", Transition("q1", '0', '1', 'R'));
	//tm1.addTransition("start", Transition("q1", '1', '1', 'R'));
	//tm1.addTransition("q1", Transition("q1", '0', '1', 'R'));
	//tm1.addTransition("q1", Transition("q1", '1', '1', 'R'));
	//tm1.addTransition("q1", Transition("halt", '_', '_', 'L'));

	//TuringMachine tm0;
	//tm0.addTransition("start", Transition("q1", '1', '0', 'R'));
	//tm0.addTransition("start", Transition("q1", '0', '0', 'R'));
	//tm0.addTransition("q1", Transition("q1", '1', '0', 'R'));
	//tm0.addTransition("q1", Transition("q1", '0', '0', 'R'));
	//tm0.addTransition("q1", Transition("halt", '_', '_', 'L'));

	////decider.saveMachine();
	////tm1.saveMachine();
	////tm0.saveMachine();
	//DeciderTM dtm(decider, tm1, tm0);
	//dtm.loadMachine();
	//dtm.runMachine();
	//std::cout << dtm.getID();
}

TEST_CASE("testing while composition") {
	Tape tape("11111110");
	TuringMachine decider;
	decider.setTape(tape);
	decider.addTransition("start", Transition("accept", '1', '1', 'H'));
	decider.addTransition("start", Transition("reject", '0', '0', 'H'));
	
	TuringMachine machine;
	machine.addTransition("start", Transition("halt", '1', 'X', 'R'));
	decider.saveMachine();
	machine.saveMachine();
	WhileComposedTM wctm;
	wctm.loadMachine();
	wctm.runMachine();
}


int main() {
	//doctest::Context().run();
	
	
	Tape tape("000001");
	WhileComposedTM wctm;
	wctm.loadMachine();
	wctm.runMachine();
}

