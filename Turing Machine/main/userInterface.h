#pragma once
#include <iostream>
#include "TuringMachine.h"
#include "SingleTapeTM.h"
#include "MultitapeTM.h"

void help() {
	std::cout << "0 - Exit program\n";
	std::cout << "1 - Run a singletape machine\n";
	std::cout << "2 - Run a multitape machine\n";
	std::cout << "3 - Run a singletape composition\n";
	std::cout << "4 - Run a multitape composition\n\n";
}

void printCompositionOptions() {
	std::cout << "What composition do you want to run?\n";
	std::cout << "1 - Linear composition\n";
	std::cout << "2 - If/Decider composition\n";
	std::cout << "3 - While composition\n";
	std::cout << "Enter choice: ";
}

void removeSpaces(std::string& sentence) {
	sentence.erase(remove(sentence.begin(), sentence.end(), ' '), sentence.end());
}

void pauseAndClear() {
	system("pause");
	system("cls");
}

void runSingleTape() {
	TuringMachine* tm = new SingleTapeTM();
	tm->loadMachine();
	if (tm->hasNoInstructions()) {
		std::cout << "Error in loading :(\n\n";
		return;
	}
	
	tm->usersTapeChoice();
	system("cls");
	tm->runMachine();
	pauseAndClear();
	
	delete tm;
}

void runMultiTape() {
	std::string singletape_choice;
	TuringMachine* tm = new MultitapeTM();
	tm->loadMachine();
	if (tm->hasNoInstructions()) {
		std::cout << "Error in loading :(\n\n";
		return;
	}
	
	tm->usersTapeChoice();
	system("cls");
	std::cout << "Do you want to run the multitape machine in singletape version?\n";
	std::cout << "1 - yes\n";
	std::cout << "2 - no\n";
	std::cout << "Enter choice: ";

	std::cin >> singletape_choice;
	removeSpaces(singletape_choice);

	while (singletape_choice != "1" && singletape_choice != "2") {
		std::cout << "Enter VALID choice: ";
		std::cin >> singletape_choice;
		removeSpaces(singletape_choice);
	}

	if (singletape_choice == "1") {
		std::cout << "Setting up machine in singletape mode...\n";
		tm->toSingleTape();
	}
	tm->runMachine();
	pauseAndClear();
	delete tm;
}

template <typename Machine>
void runLinearComp() {
	Machine tm1;
	Machine tm2;
	std::cout << "Load first singletape machine for linear composition!\n";
	tm1.loadMachine();

	if (tm1.hasNoInstructions()) {
		std::cout << "Error in loading :(\n\n";
		return;
	}
	
	tm1.usersTapeChoice();
	std::cout << "Load second singletape machine for linear composition!\n";
	tm2.loadMachine();
	tm1.linearComposition(tm2);
	pauseAndClear();
}

template <typename Machine>
void runIfComp() {
	Machine decider;
	Machine tm1;
	Machine tm0;
	std::cout << "Load decider singletape machine for if composition!\n";
	decider.loadMachine();

	if (decider.hasNoInstructions()) {
		std::cout << "Error in loading :(\n\n";
		return;
	}

	decider.usersTapeChoice();
	std::cout << "Load truth singletape machine for if composition!\n";
	tm1.loadMachine();
	std::cout << "Load false singletape machine for if composition!\n";
	tm0.loadMachine();
	decider.ifComposition(tm1, tm0);
	pauseAndClear();
}

template <typename Machine>
void runWhileComp() {
	Machine whileMachine;
	Machine doMachine;
	std::cout << "Load while singletape machine for while composition!\n";
	whileMachine.loadMachine();

	if (whileMachine.hasNoInstructions()) {
		std::cout << "Error in loading :(\n\n";
		return;
	}

	whileMachine.usersTapeChoice();
	std::cout << "Load do singletape machine for while composition!\n";
	doMachine.loadMachine();
	whileMachine.whileComposition(doMachine);
	pauseAndClear();
}

template <typename Machine>
void runCompositions() {
	std::string command;
	printCompositionOptions();
	std::cin >> command;
	removeSpaces(command);
	while (command != "1" && command != "2" && command != "3") {
		std::cout << "Enter VALID choice: ";
		std::cin >> command;
		removeSpaces(command);
	}
	
	if (command == "1") {
		runLinearComp<Machine>();
	}
	else if (command == "2") {
		runIfComp<Machine>();
	}
	else if (command == "3") {
		runWhileComp<Machine>();
	}
}

void RUN() {
	std::string command;

	while (true) {

		help();
		std::cout << "Enter command: ";
		std::cin >> command;
		removeSpaces(command);
		system("cls");
		if (command == "0") {
			std::cout << "Exiting program...\n";
			system("pause");
			break;
		}
		else if (command == "1") {
			runSingleTape();
		}
		else if (command == "2") {
			runMultiTape();
		}
		else if (command == "3") {
			runCompositions<SingleTapeTM>();
		}
		else if (command == "4") {
			runCompositions<MultitapeTM>();
		}
		else {
			std::cout << "INVALID COMMAND!\n\n";
		}
	}
}