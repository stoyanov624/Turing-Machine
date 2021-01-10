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
	// this will show us every turing machine 
	// we ever created in a folder called turing machines
	// later we can pick which machine to choose
	std::string path = "turing_machines\\";
	Menu menu;
	for (const auto& entry : fs::directory_iterator(path)) {
		menu.addChoice(entry.path().filename().string());
	}
	
	if (menu.hasNoItems()) {
		return "";
	}

	return path + menu.getChoice();
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
		//this is mainly for the multitapeturingMachine because
		//we want the number of cells we are checking to be equal 
		//to the number of tapes we have
		if (t == transition || !transition.isValid() || !transition.canWorkWith(t)) {
			std::cout << "Transition you tried to add is INVALID!\n";
			system("pause");
			return;
		}
		//this is for singletape, we have to make sure
		//if we are adding a transition to a single tape machine that 
		//the number of cells for we are checking for example is exactly 1
		if (isSingleTapeMachine() && !transition.isGoodForSingleTape()) {
			std::cout << "Transition you tried to add is INVALID!\n";
			system("pause");
			return;
		}
	}

	if ((isSingleTapeMachine() && !transition.isGoodForSingleTape()) || !transition.isValid()) {
		std::cout << "Transition you tried to add is INVALID!\n";
		system("pause");
		return;
	}

	instructions[key_to_transition].push_back(transition);
}

int TuringMachine::getID() const {
	return machine_ID;
}
// We use this to determine the exact amount of tapes from MultitapeMachine the user needs
unsigned TuringMachine::getNumberOfTapesYouNeed()  { 
	for (auto t : instructions["start"]) {
		return t.getCurrentCell().length();
	}

	return 0;
}

void TuringMachine::setCustomID() {
	std::string id = "";
	std::cout << "ID: ";
	std::cin >> id;
	id.erase(remove(id.begin(), id.end(), ' '), id.end());

	while (id.find_first_not_of("0123456789") != std::string::npos) {
		std::cout << "Id must have only numbers!\n";
		std::cout << "Enter VALID ID: ";
		std::cin >> id;
		id.erase(remove(id.begin(), id.end(), ' '), id.end());
	}
	machine_ID = std::stoi(id);
}

void TuringMachine::giveUniqueID(std::string& path) {
	
	std::cout << "A turing machine with ID  "<< machine_ID << " already exists!\n";
	std::cout << "Enter a new number ID for your machine and make it unique!\n";
	setCustomID();
	path += std::to_string(machine_ID) + ".txt";
}

bool TuringMachine::isSuccesful() const {
	return current_state == "halt" || current_state == "accept";
}

bool TuringMachine::hasNoInstructions() const {
	return instructions.empty();
}

