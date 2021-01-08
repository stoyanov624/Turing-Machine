#include <iostream>
#include "TuringMachine.h"
#include "SingleTapeTM.h"
#include "MultitapeTM.h"
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

TEST_CASE("testing tape movement,reading and writing") {
	//Tape t("123456");
	//CHECK(t.read() == "1");
	//t.move_right();
	//CHECK(t.read() == "2");
	//t.write("9");
	//CHECK(t.read() == "9");
	//t.show_tape();
}

TEST_CASE("testing tape infinity") {
	//Tape t("XXXXXX");
	//t.move_left();
	//CHECK(t.read() == "_");
	//t.move_right();
	//CHECK(t.read() == "X");
	//t.show_tape();
}

TEST_CASE("testing machine that makes everything into 1") {
	//std::cout << "\nTESTING MACHINE!\n";
	//TuringMachine tm;
	//Tape tape("0110110");
	//tm.addTape(tape);
	//tm.addTransition("start", Transition("q1", "0", "1", "R"));
	//tm.addTransition("start", Transition("q1", "1", "1", "R"));
	//tm.addTransition("q1", Transition("q1", "0", "1", "R"));
	//tm.addTransition("q1", Transition("q1", "1", "1", "R"));
	//tm.addTransition("q1", Transition("halt", "_", "_", "L"));

	//tm.runMachine();
	//std::cout << "\nTESTING DONE!\n";

}

TEST_CASE("testing decider machine") {
	//Tape t1("011011");
	//SingleTapeTM decider;
	//decider.setTape(t1);
	//decider.addTransition("start", Transition("reject", "_", "_", "H"));
	//decider.addTransition("start", Transition("q1", "1", "1", "R"));
	//decider.addTransition("start", Transition("q1", "0", "0", "R"));
	//decider.addTransition("q1", Transition("q1", "1", "1", "R"));
	//decider.addTransition("q1", Transition("q1", "0", "0", "R"));
	//decider.addTransition("q1", Transition("q2", "_", "_", "L"));
	//decider.addTransition("q2", Transition("reject", "0", "0", "H"));
	//decider.addTransition("q2", Transition("accept", "1", "1", "H"));
	//
	//SingleTapeTM tm1;
	//tm1.addTransition("start", Transition("q1", "0", "1", "R"));
	//tm1.addTransition("start", Transition("q1", "1", "1", "R"));
	//tm1.addTransition("q1", Transition("q1", "0", "1", "R"));
	//tm1.addTransition("q1", Transition("q1", "1", "1", "R"));
	//tm1.addTransition("q1", Transition("halt", "_", "_", "L"));
	//
	//SingleTapeTM tm0;
	//tm0.addTransition("start", Transition("q1", "1", "0", "R"));
	//tm0.addTransition("start", Transition("q1", "0", "0", "R"));
	//tm0.addTransition("q1", Transition("q1", "1", "0", "R"));
	//tm0.addTransition("q1", Transition("q1", "0", "0", "R"));
	//tm0.addTransition("q1", Transition("halt", "_", "_", "L"));
	//
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

void help() {
	std::cout << "0 - Exit program\n";
	std::cout << "1 - Run a singletape machine\n";
	std::cout << "2 - Run a multitape machine\n";
	std::cout << "3 - Run a singletape composition\n";
	std::cout << "4 - Run a multitape composition\n\n";
}

int main() {
	//doctest::Context().run();
	std::string command;
	
	while (true) {
		
		help();
		std::cout << "Enter command: ";
		std::cin >> command;
		system("cls");
		if (command == "0") {
			std::cout << "Exiting program...\n";
			system("pause");
			break;
		}
		else if (command == "1") {
			TuringMachine* tm = new SingleTapeTM();
			if (tm->hasNoInstructions()) {
				std::cout << "Error in loading :(\n\n";
			}
			else {
				tm->loadMachine();
				tm->usersTapeChoice();
				tm->runMachine();
				delete tm;
			}
		}
		else if (command == "2") {
			TuringMachine* tm = new MultitapeTM();
			tm->loadMachine();
			if (tm->hasNoInstructions()) {
				std::cout << "Error in loading :(\n\n";
			}
			else {
				tm->usersTapeChoice();
				tm->runMachine();
				delete tm;
			}
		}
		else if (command == "3") {

		}
		else if (command == "4") {

		}
		else {
			std::cout << "INVALID COMMAND!\n\n";
		}
		
	}
}

