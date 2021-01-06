#include "MultitapeTM.h"

MultitapeTM::MultitapeTM() : TuringMachine() {
	tapes.push_back(new Tape());
	tapes_count = 1;
	isSingleTaped = false;
}

MultitapeTM::MultitapeTM(const std::vector<Tape*>& _tapes, const std::map<std::string, std::vector<Transition>>& _instructions) : TuringMachine(_instructions) {
	tapes = _tapes;
	tapes_count = tapes.size();
	isSingleTaped = false;
}

MultitapeTM& MultitapeTM::operator=(const MultitapeTM& other_multitapeTM) {
	if (this != &other_multitapeTM) {
		tapes = other_multitapeTM.tapes;
		isSingleTaped = other_multitapeTM.isSingleTaped;
		tapes_count = other_multitapeTM.tapes_count;
		instructions = other_multitapeTM.instructions;
		machine_ID = other_multitapeTM.machine_ID;
		current_state = other_multitapeTM.current_state;
	}

	return *this;
}

void MultitapeTM::moveHeadToBeginning() {
	for (unsigned i = 0; i < tapes_count; i++) {
		tapes[i]->move_to_beginning();
	}
}

void MultitapeTM::printTape() {
	
	for (unsigned i = 0; i < tapes_count; i++) {
		std::cout << "Tape " << i + 1 << ": ";
		tapes[i]->show_tape();
	}
}

void MultitapeTM::saveResult() const {
	std::string result_file_str = "results_from_MultiTapemachines\\result" + std::to_string(machine_ID) + ".txt";
	std::ofstream resultFile(result_file_str);
	for (unsigned i = 0; i < tapes_count; i++) {
		tapes[i]->saveTape(resultFile);
	}
}

const std::vector<Tape*>& MultitapeTM::getTape() const {
	return tapes;
}


void MultitapeTM::setTape(const std::vector<Tape*>& _tapes) {
	tapes = _tapes;
}

void MultitapeTM::saveMachine() {
	std::string machine_file_str = "turing_machines\\multitape_machine" + std::to_string(machine_ID) + ".txt";
	std::ofstream machineSaveFile(machine_file_str);
	machineSaveFile << machine_ID << "\n";
	machineSaveFile << tapes_count << "\n";
	for (unsigned i = 0; i < tapes_count; i++) {
		tapes[i]->saveTape(machineSaveFile);
	}
	machineSaveFile << current_state << "\n";
	saveInstructions(machineSaveFile);
}

void MultitapeTM::loadMachine() {
	std::string path = getPathToWantedLoad();
	if (path == "") 
		return;

	if (path[path.find('\\') + 1] != 'm') {
		std::cout << "Tryng to load a singletape machine! That won't work well!";
		return;
	}
	std::ifstream in(path);

	in >> machine_ID;
	in.get();
	
	in >> tapes_count;
	in.get();
	tapes.clear();
	for (unsigned i = 0; i < tapes_count; i++) {
		Tape* t = new Tape();
		tapes.push_back(t);
		tapes[i]->loadTape(in);
	}
	std::string input;
	
	std::getline(in, input);
	current_state = input;
	loadInstructions(in);
}

void MultitapeTM::runMachine() {
	if (instructions.empty()) {
		std::cout << "Can't start the machine with no instructions!\n";
		return;
	}
	if (isSingleTaped) {
		printSingleTapeVersion();
	}
	else {
		printTape();
	}
	while (current_state != "halt" && current_state != "reject" && current_state != "accept") {
		goToNextTransition();
	}
	printFinalState();
	
	if(isSuccesful())
		saveResult();
}

void MultitapeTM::goToNextTransition() {
	bool is_good_transition = true;
	Transition good_transition;
	for (auto t : instructions[current_state]) {
		is_good_transition = true;
		for (unsigned i = 0; i < tapes_count; i++) {
			if (t.getCurrentCell()[i] != tapes[i]->read()) {
				is_good_transition = false;
				break;
			}
		}
		if (is_good_transition) {
			good_transition = t;
			break;
		}
	}

	if (is_good_transition) {
		for (unsigned i = 0; i < tapes_count; i++) {
			std::cout << i + 1 << '.' << "Current cell is " << tapes[i]->read() << " soo change it to " << good_transition.getChangeCell()[i];
			tapes[i]->write(good_transition.getChangeCell()[i]);
			switch (good_transition.getMoveDirection()[i]) {
			case 'R':
				std::cout << " and move head to the right\n";
				tapes[i]->move_right();
				break;
			case 'L':
				std::cout << " and move head to the left\n";
				tapes[i]->move_left();
				break;
			default:
				std::cout << " and don't move the head\n";
				break;
			}
		}
		current_state = good_transition.getCurrentTransition();
		std::cout << "\n";
		if (isSingleTaped) {
			printSingleTapeVersion();
		}
		else {
			printTape();
		}
		return;
	}

	current_state = "reject";
}

void MultitapeTM::toSingleTape() {
	isSingleTaped = true;
}

void MultitapeTM::printSingleTapeVersion() {
	std::string single_tape = "[#";
	for (size_t i = 0; i < tapes_count; i++) {
		single_tape += tapes[i]->tape_str();
		single_tape += "#";
	}
	single_tape += "]";
	std::cout << single_tape << std::endl;
}

