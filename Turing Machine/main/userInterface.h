#pragma once
#include <iostream>
#include <typeinfo>
#include "TuringMachine.h"
#include "SingleTapeTM.h"
#include "MultitapeTM.h"

void help() {
	std::cout << "0 - Exit program\n";
	std::cout << "1 - Run a singletape machine\n";
	std::cout << "2 - Run a multitape machine\n";
	std::cout << "3 - Run a singletape composition\n";
	std::cout << "4 - Run a multitape composition\n";
	std::cout << "5 - Create a singletape machine\n";
	std::cout << "6 - Create a multitape machine\n\n";
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

template <typename Machine>
void addTransitionToMachine(Machine& tm) {
	Transition transition;
	std::string choice;
	std::string state;

	while (choice != "yes") {
		std::cout << "To which state do you want to add this transition?\n";
		std::cout << "Enter info: ";
		std::cin >> state;

		std::cout << "Which will be the next state?\n";
		std::cout << "Enter info: ";
		std::cin >> choice;
		transition.setCurrentTransition(choice);

		std::cout << "What cell/cells need to be read to go to next state?\n";
		std::cout << "Enter info: ";
		std::cin >> choice;
		transition.setCurrentCell(choice);

		std::cout << "How will you change the cell/s\n";
		std::cout << "Enter info: ";
		std::cin >> choice;
		transition.setChangeCell(choice);

		std::cout << "How do you want the tape to move? (R/L/H)\n";
		std::cout << "Enter info: ";
		std::cin >> choice;
		transition.setMoveDirection(choice);
		tm.addTransition(state, transition);

		std::cout << "Are you done adding transitions? (yes/no)";
		std::cin >> choice;
		system("cls");
	}
}

template <typename Machine>
void createMachine() {
	Machine tm;
	addTransitionToMachine(tm);
	std::cout << "Enter unique ID!\n";
	tm.setCustomID();
	system("cls");
	std::cout << "Enter tape/s\n";
	tm.usersTapeChoice(true);
	system("cls");

	tm.saveMachine();
	std::cout << "Machine succesfully saved!\n";
	system("pause");
	system("cls");
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
		else if (command == "5") {
			createMachine<SingleTapeTM>();
		}
		else if (command == "6") {
			createMachine<MultitapeTM>();
		}
		else {
			std::cout << "INVALID COMMAND!\n\n";
		}
	}
}