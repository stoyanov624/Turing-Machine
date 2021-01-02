#include <iostream>
#include "TuringMachine.h"
#include "LinearComposedTM.h"
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

TEST_CASE("composition of two turing machines") {
	TuringMachine tm;
	Tape tape("000000000000");
	tm.setTape(tape);
	tm.addTransition("start", Transition("q1", '0', '1', 'R'));
	tm.addTransition("start", Transition("q1", '1', '1', 'R'));
	tm.addTransition("q1", Transition("q1", '0', '1', 'R'));
	tm.addTransition("q1", Transition("q1", '1', '1', 'R'));
	tm.addTransition("q1", Transition("halt", '_', '_', 'L'));
	tm.addTransition("q1", Transition("halt", '_', '_', 'L'));
	tm.addTransition("q1", Transition("halt", '_', '_', 'L'));
	tm.addTransition("q1", Transition("halt", '_', '_', 'L'));
	std::ofstream someFile("sss.txt");
	tm.saveMachine(someFile);
	//tm.runMachine();
	
	//TuringMachine tm2;
	//Tape tape2("0110110");
	//tm2.setTape(tape2);
	//tm2.addTransition("start", Transition("reject", '0', '0', 'H'));
	//tm2.addTransition("start", Transition("q2", '1', '1', 'R'));
	//tm2.addTransition("q2", Transition("start", '1', '0', 'R'));
	//tm2.addTransition("q2", Transition("reject", '0', '0', 'H'));
	//tm2.addTransition("q2", Transition("halt", '_', '_', 'L'));
	//tm2.addTransition("start",Transition("halt",'_','_','L'));
	//
	//LinearComposedTM tm3(tm, tm2);
	////tm3.runMachine();
	//tm3.printTape();
}


int main() {

	doctest::Context().run();
}

