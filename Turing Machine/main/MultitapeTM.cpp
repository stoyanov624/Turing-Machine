#include "MultitapeTM.h"

MultitapeTM::MultitapeTM() : TuringMachine() {
	tapes.push_back(new Tape());
	tapes_count = 1;
	isSingleTaped = false;
}

MultitapeTM::MultitapeTM(int _machine_ID, const std::vector<Tape*>& _tapes, const std::map<std::string, std::vector<Transition>>& _instructions) : TuringMachine(_machine_ID,_instructions) {
	//this makes sure we always have atleast one tape to work with.
	if (!_tapes.empty()) {
		tapes = _tapes;
		tapes_count = tapes.size();
	}
	else {
		tapes.push_back(new Tape());
		tapes_count = 1;
	}
	
	isSingleTaped = false;
}

MultitapeTM& MultitapeTM::operator=(const MultitapeTM& other_multitapeTM) {
	if (this != &other_multitapeTM) {
		tapes = other_multitapeTM.tapes;
		isSingleTaped = other_multitapeTM.isSingleTaped;
		tapes_count = other_multitapeTM.tapes_count;
		TuringMachine::operator=(other_multitapeTM);
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

const std::vector<Tape*>& MultitapeTM::getTape() {
	return tapes;
}

void MultitapeTM::setTape(const std::vector<Tape*>& _tapes) {
	tapes = _tapes;
}

void MultitapeTM::saveMachine() {

	if (!fs::is_directory("turing_machines") || !fs::exists("turing_machines"))
		fs::create_directory("turing_machines");

	std::string machine_file_str = "turing_machines\\multitape_machine" + std::to_string(machine_ID) + ".txt";
	while (fs::exists(machine_file_str)) {
		machine_file_str = "turing_machines\\multitape_machine";
		giveUniqueID(machine_file_str);
	}

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

	if (!fs::is_directory("turing_machines") || !fs::exists("turing_machines"))
		fs::create_directory("turing_machines");

	std::string path = getPathToWantedLoad();

	if (path == "") {
		std::cout << "No machine to load! Folder empty!\n";
		return;
	}
	// because we keep singletape turing machines and multitape 
	//turing machines in the same folder I am making sure someone 
	//doesn't load a singleTape TM for a multiTape one
	if (path[path.find('\\') + 1] != 'm') {
		std::cout << "Trying to load a singletape machine! That won't work well!\n";
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

void MultitapeTM::linearComposition(MultitapeTM& second_tm) {
	runMachine();
	if (isSuccesful()) {
		moveHeadToBeginning();
		second_tm.tapes = tapes;
		second_tm.tapes_count = tapes_count;
		second_tm.isSingleTaped = isSingleTaped;
		second_tm.runMachine();
	}
	else {
		std::cout << "First machine didn't end!\n";
		return;
	}

	if (!fs::is_directory("results_from_LC_machines") || !fs::exists("results_from_LC_machines"))
		fs::create_directory("results_from_LC_machines");

	std::string result_file_str = "results_from_LC_machines\\LCresult" + std::to_string(machine_ID + second_tm.machine_ID) + ".txt";
	std::ofstream resultFile(result_file_str);
	for (unsigned i = 0; i < tapes_count; i++) {
		second_tm.tapes[i]->saveTape(resultFile);
	}
}

void MultitapeTM::ifComposition(MultitapeTM& tm1, MultitapeTM& tm0) {
	std::vector<Tape*> saveTape = tapes;
	bool first_machine_ran = true;
	runMachine();
	if (isSuccesful()) {
		tm1.tapes = saveTape;
		tm1.tapes_count = tapes_count;
		tm1.isSingleTaped = isSingleTaped;
		tm1.moveHeadToBeginning();
		tm1.runMachine();

	}
	else {
		tm0.tapes = saveTape;
		tm0.tapes_count = tapes_count;
		tm0.isSingleTaped = isSingleTaped;
		tm0.moveHeadToBeginning();
		tm0.runMachine();
		first_machine_ran = false;
	}
   
	if (!fs::is_directory("results_from_Decider_machines") || !fs::exists("results_from_Decider_machines"))
		fs::create_directory("results_from_Decider_machines");

	std::string result_file_str = "results_from_Decider_machines\\result" 
									+ std::to_string(machine_ID + tm1.machine_ID + tm0.machine_ID) + ".txt";
	std::ofstream resultFile(result_file_str);
	for (unsigned i = 0; i < tapes_count; i++) {
		if (first_machine_ran) {
			tm1.tapes[i]->saveTape(resultFile);
		}
		else {
			tm0.tapes[i]->saveTape(resultFile);
		}
	}
}

void MultitapeTM::whileComposition(MultitapeTM& tm) {
	tm.tapes = tapes;
	tm.tapes_count = tapes_count;
	tm.isSingleTaped = isSingleTaped;
	runMachine();
	while (isSuccesful()) {
		tm.tapes = tapes;
		tm.runMachine();
		tm.goToStart();

		tapes = tm.tapes;
		goToStart();
		runMachine();
	}

	if (!fs::is_directory("results_from_While_machines") || !fs::exists("results_from_While_machines"))
		fs::create_directory("results_from_While_machines");

	std::string result_file_str = "results_from_While_machines\\Whileresult" + std::to_string(machine_ID + tm.machine_ID) + ".txt";
	std::ofstream resultFile(result_file_str);
	for (unsigned i = 0; i < tapes_count; i++) {
		tm.tapes[i]->saveTape(resultFile);
	}
}

void MultitapeTM::runMachine() {
	if (instructions.empty()) {
		std::cout << "Can't start the machine with no instructions!\n";
		return;
	}

	if (tapes.empty()) {
		std::cout << "Can't start the machine with no tapes!\n";
		return;
	}
	if (isSingleTaped) {
		printSingleTapeVersion();
	}
	else {
		printTape();
	}
	goToStart();
	while (current_state != "halt" && current_state != "reject" && current_state != "accept") {
		goToNextTransition();
	}
	printFinalState();
	
	if(isSuccesful())
		saveResult();
}

void MultitapeTM::goToNextTransition() {
	// we are looking for a transition that can go to 
	//another state if the head is looking at the correct elements on the correct tapes
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

void MultitapeTM::toMultiTape() {
	isSingleTaped = false;
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

void MultitapeTM::usersTapeChoice(bool isGettingCreated) {
	std::string choice = "";
	if (isGettingCreated) {
		tapes_count = getNumberOfTapesYouNeed();
		tapes.clear();
		for (unsigned i = 0; i < tapes_count; i++) {
			std::cout << "Enter tape " << i + 1 << ": ";
			std::cin >> choice;
			tapes.push_back(new Tape());
			tapes[i]->initializeTape(choice);
		}
		std::cout << std::endl;
		return;
	}
	Menu menu;
	menu.addChoice("Enter custom tapes");
	menu.addChoice("Use tapes from machine you loaded");

	switch (menu.getIndexChoice()) {
	case 0:
		system("cls");
		tapes_count = getNumberOfTapesYouNeed();
		tapes.clear();
		for (unsigned i = 0; i < tapes_count; i++) {
			std::cout << "Enter tape " << i + 1 << ": ";
			std::cin >> choice;
			tapes.push_back(new Tape());
			tapes[i]->initializeTape(choice);
		}
		std::cout << std::endl;
		return;
	}
	system("cls");
	std::cout << "Okay we will use the tape from the machine you loaded!\n";
	system("pause");
	return;
	
}

bool MultitapeTM::isSingleTapeMachine() const {
	return false;
}