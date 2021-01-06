#include "TuringMachine.h"
//#include "windows.h"
int TuringMachine::machine_ID_generator = 1000;

TuringMachine::TuringMachine() {
	current_state = "start";
	machine_ID = machine_ID_generator++;
}

TuringMachine::TuringMachine(const std::map<std::string, std::vector<Transition>>& other_instructions) {
	current_state = "start";
	instructions = other_instructions;
	machine_ID = machine_ID_generator++;
}

void TuringMachine::goToStart() {
	current_state = "start";
}

void TuringMachine::saveInstructions(std::ofstream& out) {
	for (std::map<std::string, std::vector<Transition>>::reverse_iterator key = instructions.rbegin(); key != instructions.rend(); key++) {
		for (auto value : key->second) {
			out << value.getCurrentCell() << "{" << key->first << "}" << " -> " << value.getChangeCell() << "{" 
				<< value.getCurrentTransition() << "}" << value.getMoveDirection() << "\n";
		}
	}
}

const std::string TuringMachine::getPathToWantedLoad() {
	std::string path = "turing_machines";
	unsigned number = 1;
	std::vector<std::string> filenames;

	for (const auto& entry : fs::directory_iterator(path)) {
		filenames.push_back(entry.path().string());
		std::cout << number << " - " << entry.path().filename() << std::endl;
		number++;
	}
	if (number == 1) {
		std::cout << "No turing machines saved for you to load!\n";
		return "";
	}
	std::cout << "Enter number: ";
	std::cin >> number;
	std::cout << std::endl;

	while (number <= 0 || number > filenames.size()) {
		std::cout << "Enter VALID number: ";
		std::cin >> number;
	}
	path = filenames[number - 1];
	return path;
}

void TuringMachine::instructionDeserializer(const std::string& input) {
	std::string current_cells = input.substr(0, input.find('{'));
	std::string change_cells = "";
	std::string current_state = "";
	std::string next_state = "";
	std::string move_commands = "";

	unsigned position = current_cells.length() + 1;
	while (input[position] != '}') {
		current_state += input[position];
		position++;
	}
	position += 5;
	change_cells = input.substr(position, input.find('{'));
	position += change_cells.length() + 1;
	while (input[position] != '}') {
		next_state += input[position];
		position++;
	}
	position++;

	move_commands = input.substr(position, input.length());
	addTransition(current_state, Transition(next_state, current_cells, change_cells, move_commands));
}

void TuringMachine::loadInstructions(std::ifstream& in) {
	instructions.clear();
	std::string input;

	while (std::getline(in, input)) {
		instructionDeserializer(input);
	}
}

void TuringMachine::addTransition(const std::string& key_to_transition,const Transition& transition) {
	for (auto t : instructions[key_to_transition]) {
		if (t == transition) 
			return;
	}
	instructions[key_to_transition].push_back(transition);
}

int TuringMachine::getID() const {
	return machine_ID;
}

bool TuringMachine::isSuccesful() const {
	return current_state == "halt" || current_state == "accept";
}

//void TuringMachine::usersTapeChoice() {
//	std::string choice;
//	std::cout << "Do you want to enter a custom tape or use the tape from first machine you loaded?\n";
//	std::cout << "1 - Enter custom tape\n";
//	std::cout << "2 - Use tape from first machine\n";
//	std::cout << "Your choice: ";
//	std::cin >> choice;
//	while (choice != "1" && choice != "2") {
//		std::cout << "Enter VALID number: ";
//		std::cin >> choice;
//	}
//
//	if (choice == "1") {
//		std::cout << "Enter tape: ";
//		std::cin >> choice;
//		tape.initializeTape(choice);
//		std::cout << std::endl;
//	}
//	else {
//		std::cout << "Okay we will use the tape from the first machine you loaded\n!";
//		return;
//	}
//}
