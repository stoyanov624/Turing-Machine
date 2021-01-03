#include "TuringMachine.h"

int TuringMachine::machine_ID_generator = 1000;

TuringMachine::TuringMachine() {
	current_state = "start";
	machine_ID = machine_ID_generator++;
}

TuringMachine::TuringMachine(const Tape& other_tm_tape, 
							 const std::map<std::string, std::vector<Transition>>& other_instructions) {
	tape = other_tm_tape;
	current_state = "start";
	instructions = other_instructions;
	machine_ID = machine_ID_generator++;
}

TuringMachine& TuringMachine::operator=(const TuringMachine& other_machine) {
	if (this != &other_machine) {
		machine_ID = other_machine.machine_ID;
		tape = other_machine.tape;
		current_state = other_machine.current_state;
		instructions = other_machine.instructions;
	}
	
	return *this;
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
	current_state = "reject";
}

void TuringMachine::goToStart() {
	current_state = "start";
}

void TuringMachine::moveHeadToBeginning() {
	tape.move_to_beginning();
}

void TuringMachine::saveInstructions(std::ofstream& out) {
	for (std::map<std::string, std::vector<Transition>>::reverse_iterator key = instructions.rbegin(); key != instructions.rend(); key++) {
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

void TuringMachine::saveMachine() {
	std::string machine_file_str = "simple_turing_machines\\machine" + std::to_string(machine_ID) + ".txt";
	std::ofstream machineSaveFile(machine_file_str);
	machineSaveFile << machine_ID << "\n";
	tape.saveTape(machineSaveFile);
	machineSaveFile << current_state << "\n";
	saveInstructions(machineSaveFile);
}

void TuringMachine::loadMachine() {
	std::string path = "simple_turing_machines";
	int number = 1;
	std::vector<std::string> filenames;

	for (const auto& entry : fs::directory_iterator(path)) {
		filenames.push_back(entry.path().string());
		std::cout << number << " - " << entry.path().filename() << std::endl;
		number++;
	}

	std::cout << "Enter number: ";
	std::cin >> number;
	std::cout << std::endl;

	while (number <= 0 || number > filenames.size()) {
		std::cout << "Enter VALID number: ";
		std::cin >> number;
	}
	path = filenames[number - 1];

	std::ifstream in(path);
	in >> machine_ID;
	in.get();
	tape.loadTape(in);
	std::string input;
	std::getline(in, input);
	current_state = input;
	loadInstructions(in);
}

void TuringMachine::loadInstructions(std::ifstream& in) {
	instructions.clear();
	std::string input;

	while (std::getline(in, input)) {
		instructionDeserializer(input);
	}
}

void TuringMachine::saveResult() const {
	std::string result_file_str = "results_from_machines\\result" + std::to_string(machine_ID) + ".txt";
	std::ofstream resultFile(result_file_str);
	tape.saveTape(resultFile);
}

void TuringMachine::runMachine() {
	tape.show_tape();
	while(current_state != "halt" && current_state != "reject" && current_state != "accept") {
		goToNextTransition();
	}
	if (current_state == "halt") {
		std::cout << "\nMACHINE " << machine_ID << " HALTED!\n\n";
	}
	else if (current_state == "accept") {
		std::cout << "\nMACHINE" << machine_ID << " ACCEPTED YOUR WORD\n\n";
	}
	else if (current_state == "reject") {
		std::cout << "\nMACHINE" << machine_ID << " REJECTED YOUR WORD\n\n";
	}
	saveResult();
}

void TuringMachine::addTransition(const std::string& key_to_transition, Transition transition) {
	for (auto t : instructions[key_to_transition]) {
		if (t == transition) 
			return;
	}
	instructions[key_to_transition].push_back(transition);
}

const Tape& TuringMachine::getTape() const {
	return tape;
}

int TuringMachine::getID() const {
	return machine_ID;
}

void TuringMachine::setTape(const Tape& _tape) {
	tape = _tape;
	//tape.move_to_beginning();
}

void TuringMachine::printTape() {
	tape.show_tape();
}

bool TuringMachine::isSuccesful() const {
	return current_state == "halt" || current_state == "accept";
}
