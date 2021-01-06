#include "MultitapeTM.h"

MultitapeTM::MultitapeTM() : TuringMachine(),tapes() {
	tapes_count = 0;
}

MultitapeTM::MultitapeTM(const std::vector<Tape*>& _tapes, const std::map<std::string, std::vector<Transition>>& _instructions) : TuringMachine(_instructions) {
	tapes = _tapes;
	tapes_count = tapes.size();
}

MultitapeTM& MultitapeTM::operator=(const MultitapeTM& other_multitapeTM) {
	if (this != &other_multitapeTM) {
		tapes = other_multitapeTM.tapes;
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

	std::ifstream in(path);

	in >> machine_ID;
	in.get();
	
	in >> tapes_count;
	in.get();
	tapes.clear();
	for (int i = 0; i < tapes_count; i++) {
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

}

void MultitapeTM::goToNextTransition() {

}

