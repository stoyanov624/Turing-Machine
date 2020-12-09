#include "TuringMachine.h"

TuringMachine::TuringMachine() {
	current_state = "start";
}

TuringMachine::TuringMachine(const Tape& other_tm_tape, 
							 const std::map<std::string, std::vector<Transition>>& other_instructions) {
	tape = other_tm_tape;
	current_state = "start";
	instructions = other_instructions;
}

void TuringMachine::goToNextTransition() {
	for (auto t : instructions[current_state]) {
		if (t.getCurrentCell() == tape.read()) {

			std::cout << "Current cell is " << t.getCurrentCell()
					  << " soo change it to " << t.getChangeCell();

			tape.write(t.getChangeCell());

			switch (t.getMoveDirection()) {
			case 'R':
				std::cout << " and move head to the right!\n";
				tape.move_right();
				break;
			case 'L':
				std::cout << " and move head to the left!\n";
				tape.move_left();
				break;
			default:
				std::cout << " and don't move the head!\n";
				break;
			}
			current_state = t.getCurrentTransition();
			
			tape.show_tape();
			return;
		}
	}
	std::cout << "REJECTED!\n";
	current_state = "reject";
}

void TuringMachine::saveInstructions(std::ofstream& out) {
	for (std::map<std::string, std::vector<Transition>>::reverse_iterator key = instructions.rbegin(); key != instructions.rend(); ++key) {
		for (auto value : key->second) {
			out << value.getCurrentCell() << "{" << key->first << "}" << " -> " << value.getChangeCell() << "{" 
				<< value.getCurrentTransition() << "}" << value.getMoveDirection() << "\n";
		}
	}
}

void TuringMachine::instructionDeserializer(const std::string& input) {
	unsigned length = input.length();
	char current_cell = input[0];
	char change_cell = ' ';
	char direction_command = input[length - 1];
	std::string current_state = "";
	std::string transition_state = "";
	bool current_state_not_taken = true;

	for (unsigned i = 1; i < length - 1; i++) {
		if (input[i - 1] == '{' && current_state.empty()) {
			while (input[i] != '}') {
				current_state += input[i];
				i++;
			}
		}

		if (change_cell == ' ' && !current_state.empty()) {
			i += 5;
			change_cell = input[i];
		}

		if (input[i - 1] == '{' && transition_state.empty()) {
			while (input[i] != '}') {
				transition_state += input[i];
				i++;
			}
		}
	}

	addTransition(current_state, Transition(transition_state, current_cell, change_cell, direction_command));
}

void TuringMachine::saveMachine(std::ofstream& out) {
	tape.saveTape(out);
	out << current_state << "\n";
	saveInstructions(out);
}

void TuringMachine::loadMachine(std::ifstream& in) {
	std::string input;
	tape.loadTape(in);
	std::getline(in, input);
	current_state = input;
	loadInstructions(in);
}

void TuringMachine::loadInstructions(std::ifstream& in) {
	std::string input;

	while (std::getline(in, input)) {
		instructionDeserializer(input);
	}
}

void TuringMachine::runMachine() {
	tape.show_tape();
	while(current_state != "halt" && current_state != "reject") {
		goToNextTransition();
	}
	if (current_state == "halt") {
		std::cout << "HALTED!\n";
	}
}

void TuringMachine::addTransition(const std::string& key_to_transition, Transition transition) {
	instructions[key_to_transition].push_back(transition);
}

void TuringMachine::addTape(const Tape& _tape) {
	tape = _tape;
}

void TuringMachine::printTape() {
	tape.show_tape();
}

bool TuringMachine::isSuccesful() const {
	return current_state == "halt" || current_state == "accept";
}

void TuringMachine::composition(TuringMachine& other_machine) {
	runMachine();
	if (isSuccesful()) {
		other_machine.tape = tape;
		other_machine.tape.move_to_beginning();
		other_machine.runMachine();
	}
	else {
		std::cout << "First Turing machine did not reach halt state! Composition not possible!\n";
	}
	
}