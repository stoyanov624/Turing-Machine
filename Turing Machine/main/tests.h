#pragma once
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
	//Tape tape("0110110");
	//TuringMachine* tm = new SingleTapeTM(745,tape);
	//
	//tm->addTransition("start", Transition("q1", "0", "1", "R"));
	//tm->addTransition("start", Transition("q1", "1", "1", "R"));
	//tm->addTransition("q1", Transition("q1", "0", "1", "R"));
	//tm->addTransition("q1", Transition("q1", "1", "1", "R"));
	//tm->addTransition("q1", Transition("halt", "_", "_", "L"));
	//
	//tm->runMachine();
	//tm->saveMachine();
	//delete tm;
}

TEST_CASE("testing linear composition with loading machines") {
	//SingleTapeTM tm1(5555);
	//tm1.loadMachine();
	//tm1.usersTapeChoice();
	//
	//SingleTapeTM tm2;
	//tm2.loadMachine();
	//
	//tm1.linearComposition(tm2);
}

TEST_CASE("testing decider machine") {
	//Tape t1("011011");
	//SingleTapeTM decider(1233,t1); // machine that accepts if the last element is 1 and rejects if the last element is 0
	//
	//decider.addTransition("start", Transition("reject", "_", "_", "H"));
	//decider.addTransition("start", Transition("q1", "1", "1", "R"));
	//decider.addTransition("start", Transition("q1", "0", "0", "R"));
	//decider.addTransition("q1", Transition("q1", "1", "1", "R"));
	//decider.addTransition("q1", Transition("q1", "0", "0", "R"));
	//decider.addTransition("q1", Transition("q2", "_", "_", "L"));
	//decider.addTransition("q2", Transition("reject", "0", "0", "H"));
	//decider.addTransition("q2", Transition("accept", "1", "1", "H"));
	//
	//SingleTapeTM tm1; // machine that makes everything into 1
	//tm1.addTransition("start", Transition("q1", "0", "1", "R"));
	//tm1.addTransition("start", Transition("q1", "1", "1", "R"));
	//tm1.addTransition("q1", Transition("q1", "0", "1", "R"));
	//tm1.addTransition("q1", Transition("q1", "1", "1", "R"));
	//tm1.addTransition("q1", Transition("halt", "_", "_", "L"));
	//
	//SingleTapeTM tm0; // machine that makes everything into 0
	//tm0.addTransition("start", Transition("q1", "1", "0", "R"));
	//tm0.addTransition("start", Transition("q1", "0", "0", "R"));
	//tm0.addTransition("q1", Transition("q1", "1", "0", "R"));
	//tm0.addTransition("q1", Transition("q1", "0", "0", "R"));
	//tm0.addTransition("q1", Transition("halt", "_", "_", "L"));
	//tm0.saveMachine();
	//decider.ifComposition(tm1,tm0);

}

TEST_CASE("testing while composition") {
	//Tape tape("11111110");
	//SingleTapeTM decider(tape);
	//decider.addTransition("start", Transition("accept", "1", "1", "H"));
	//decider.addTransition("start", Transition("reject", "0", "0", "H"));
	//
	//SingleTapeTM machine;
	//machine.addTransition("start", Transition("halt", "1", "X", "R"));
	//decider.saveMachine();
	//machine.saveMachine();
	//
	//decider.whileComposition(machine);
}

TEST_CASE("testing multitape machine") {
	//TuringMachine* tm = new MultitapeTM(3213);
	//tm->addTransition("start", Transition("q1", "111", "XYZ", "RRR"));
	//tm->addTransition("start",Transition("q1","000","XYZ","RRR"));
	//tm->addTransition("q1", Transition("q1", "111", "XYZ", "RRR"));
	//tm->addTransition("q1", Transition("q1", "000", "XYZ", "RRR"));
	//tm->addTransition("q1", Transition("q1", "_0_", "_Y_", "HRH"));
	//tm->addTransition("q1", Transition("halt", "___", "___", "LLL"));
	//tm->usersTapeChoice();
	//tm->toSingleTape();
	//tm->runMachine();
}

TEST_CASE("testing multitape linear composition") {
	//MultitapeTM tm(3213);
	//tm.addTransition("start", Transition("q1", "111", "XYZ", "RRR"));
	//tm.addTransition("start", Transition("q1", "000", "XYZ", "RRR"));
	//tm.addTransition("q1", Transition("q1", "111", "XYZ", "RRR"));
	//tm.addTransition("q1", Transition("q1", "000", "XYZ", "RRR"));
	//tm.addTransition("q1", Transition("q1", "_0_", "_Y_", "HRH"));
	//tm.addTransition("q1", Transition("halt", "___", "___", "LLL"));
	//tm.usersTapeChoice();
	//tm.saveMachine();
	//MultitapeTM tm2(1111);
	//tm2.addTransition("start", Transition("q1", "XYZ", "123", "RRR"));
	//tm2.addTransition("q1", Transition("q1", "XYZ", "123", "RRR"));
	//tm2.addTransition("q1", Transition("q1", "_Y_", "_2_", "HRH"));
	//tm2.addTransition("q1", Transition("halt", "___", "___", "LLL"));
	//tm.saveMachine();
	//tm.linearComposition(tm2);
	
}

TEST_CASE("testing multitape while composition") {
	//MultitapeTM tm(3435);
	//tm.addTransition("start", Transition("accept", "111", "111", "HHH"));
	//tm.addTransition("start", Transition("reject", "000", "000", "HHH"));
	//tm.addTransition("start", Transition("reject", "___", "___", "LLL"));
	////tm.usersTapeChoice();
	//tm.saveMachine();
	//MultitapeTM tm2(1545);
	//tm2.addTransition("start", Transition("halt", "111", "ONE", "RRR"));
	//tm2.saveMachine();
	//tm.toSingleTape();
	//tm.whileComposition(tm2);
}

TEST_CASE("testing multitape if composition") {
	//MultitapeTM tm(456);
	//tm.addTransition("start", Transition("accept", "111", "111", "HHH"));
	//
	//MultitapeTM tm1(432);
	//tm1.addTransition("start", Transition("halt", "111", "ONE", "HHH"));
	//
	//MultitapeTM tm0(100);
	//tm0.addTransition("start", Transition("halt", "000", "NUL", "HHH"));
	//tm0.addTransition("start", Transition("halt", "100", "NUL", "HHH"));
	//tm0.addTransition("start", Transition("halt", "010", "NUL", "HHH"));
	//tm0.addTransition("start", Transition("halt", "001", "NUL", "HHH"));
	//tm0.addTransition("start", Transition("halt", "110", "NUL", "HHH"));
	//tm0.addTransition("start", Transition("halt", "101", "NUL", "HHH"));
	//tm0.addTransition("start", Transition("halt", "011", "NUL", "HHH"));
	//tm.saveMachine();
	//tm1.saveMachine();
	//tm0.saveMachine();
	//tm.usersTapeChoice();
	//tm.ifComposition(tm1, tm0);

	
}

void runTests() {
	doctest::Context().run();
}
