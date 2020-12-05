#include "TuringMachine.h"

TuringMachine::TuringMachine() {
	current_state = "start";
}

TuringMachine::TuringMachine(Tape* other_tm_tape, 
							 const std::map<std::string, std::vector<Transition*>>& other_instructions) {
	tape = other_tm_tape;
	current_state = "start";
	instructions = other_instructions;
}

void TuringMachine::goToNextTransition() {
	for (auto t : instructions[current_state]) {
		if (t->getCurrentCell() == tape->read()) {
			std::cout << "Current cell is " << tape->read() 
					  << " soo change it to " << t->getChangeCell() 
				      << " and move head to " << t->getMoveDirection() 
				      << "\n";
			tape->write(t->getChangeCell());
			switch (t->getMoveDirection()) {
			case 'R':
				tape->move_right();
				break;
			case 'L':
				tape->move_left();
				break;
			default:
				break;
			}
			current_state = t->getCurrentTransition();
			
			tape->show_tape();
			return;
		}
	}
	std::cout << "Invalid instructions!\n";
	current_state = "";
}

void TuringMachine::runMachine() {
	printTape();
	while(current_state != "halt" && current_state != "") {
		goToNextTransition();
	}
	printTape();
}

void TuringMachine::addTransition(Transition* transition) {
	instructions[current_state].push_back(transition);
}

void TuringMachine::printTape() {
	tape->show_tape();
}