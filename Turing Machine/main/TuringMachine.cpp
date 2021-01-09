#include "TuringMachine.h"

TuringMachine::TuringMachine() {
	current_state = "start";
	machine_ID = 0;
}

TuringMachine::TuringMachine(int _machine_ID,const std::map<std::string, std::vector<Transition>>& other_instructions) {
	current_state = "start";
	instructions = other_instructions;
	machine_ID = _machine_ID;
}

TuringMachine& TuringMachine::operator=(const TuringMachine& other_tm) {
	if (this != &other_tm) {
		current_state = other_tm.current_state;
		instructions = other_tm.instructions;
		machine_ID = other_tm.machine_ID;
	}

	return *this;
}

void TuringMachine::goToStart() {
	current_state = "start";
}

void TuringMachine::printUsersChoices() const {
	std::cout << "Do you want to enter a custom tape or use the tape from machine you loaded?\n";
	std::cout << "1 - Enter custom tape\n";
	std::cout << "2 - Use tape from first machine\n";
	std::cout << "Your choice: ";
}

void TuringMachine::printFinalState() const {
	if (current_state == "halt") {
		std::cout << "\nMACHINE " << machine_ID << " HALTED!\n\n";
	}
	else if (current_state == "accept") {
		std::cout << "\nMACHINE" << machine_ID << " ACCEPTED YOUR WORD\n\n";
	}
	else if (current_state == "reject") {
		std::cout << "\nMACHINE" << machine_ID << " REJECTED YOUR WORD\n\n";
	}
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
		if (t == transition || !transition.isValid() || !transition.canWorkWith(t)) {
			std::cout << "Transition " << transition.getCurrentTransition() << " you tried to add is INVALID!\n";
			return;
		}
	}
	instructions[key_to_transition].push_back(transition);
}

int TuringMachine::getID() const {
	return machine_ID;
}

unsigned TuringMachine::getNumberOfTapesYouNeed()  {
	for (auto t : instructions["start"]) {
		return t.getCurrentCell().length();
	}

	return 0;
}

bool TuringMachine::isSuccesful() const {
	return current_state == "halt" || current_state == "accept";
}

bool TuringMachine::hasNoInstructions() const {
	return instructions.empty();
}

