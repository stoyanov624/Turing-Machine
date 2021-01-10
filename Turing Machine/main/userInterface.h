#pragma once
#include <iostream>
#include "TuringMachine.h"
#include "SingleTapeTM.h"
#include "MultitapeTM.h"
#include "Menu.h"

void makeMenu(Menu& menu) {
	menu.addChoice("Exit program");
	menu.addChoice("Run a singletape machine");
	menu.addChoice("Run a multitape machine");
	menu.addChoice("Run a singletape composition");
	menu.addChoice("Run a multitape composition");
	menu.addChoice("Create a singletape machine");
	menu.addChoice("Create a multitape machine");
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
		pauseAndClear();
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
		pauseAndClear();
		return;
	}
	
	tm->usersTapeChoice();
	system("cls");
	Menu menu;
	menu.addChoice("Launch multitape machine in singletape mode");
	menu.addChoice("Launch multitape machine in multitape mode");

	if (menu.getIndexChoice() == 0) {
		std::cout << "Setting up machine in singletape mode...\n";
		system("pause");
		system("cls");
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
	std::cout << "Loading first machine..\n";
	pauseAndClear();
	tm1.loadMachine();
	
	if (tm1.hasNoInstructions()) {
		std::cout << "Error in loading :(\n\n";
		pauseAndClear();
		return;
	}
	
	tm1.usersTapeChoice();
	std::cout << "Loading second machine..\n";
	pauseAndClear();
	tm2.loadMachine();
	tm1.linearComposition(tm2);
	pauseAndClear();
}

template <typename Machine>
void runIfComp() {
	Machine decider;
	Machine tm1;
	Machine tm0;
	std::cout << "Loading decider machine..\n";
	pauseAndClear();
	decider.loadMachine();

	if (decider.hasNoInstructions()) {
		std::cout << "Error in loading :(\n\n";
		pauseAndClear();
		return;
	}

	decider.usersTapeChoice();
	std::cout << "Loading truth machine..\n";
	pauseAndClear();
	tm1.loadMachine();
	std::cout << "Loading false machine..\n";
	pauseAndClear();
	tm0.loadMachine();
	decider.ifComposition(tm1, tm0);
	pauseAndClear();
}

template <typename Machine>
void runWhileComp() {
	Machine whileMachine;
	Machine doMachine;
	std::cout << "Loading while singletape machine for while composition..\n";
	pauseAndClear();
	whileMachine.loadMachine();

	if (whileMachine.hasNoInstructions()) {
		std::cout << "Error in loading :(\n\n";
		pauseAndClear();
		return;
	}

	whileMachine.usersTapeChoice();
	std::cout << "Loading do singletape machine for while composition..\n";
	pauseAndClear();
	doMachine.loadMachine();
	whileMachine.whileComposition(doMachine);
	pauseAndClear();
}

template <typename Machine>
void runCompositions() {
	Menu menu;
	menu.addChoice("Launch linear composition");
	menu.addChoice("Launch decider composition");
	menu.addChoice("Launch while composition");
	
	switch (menu.getIndexChoice()) {
	case 0:
		runLinearComp<Machine>();
		break;
	case 1:
		runIfComp<Machine>();
		break;
	case 2:
		runWhileComp<Machine>();
		break;
	}
}

template <typename Machine>
void addTransitionToMachine(Machine& tm) {
	Transition transition;
	std::string choice;
	std::string state;
	Menu menu;
	menu.addChoice("Add another transition");
	menu.addChoice("Exit creating stage");
	int end_choice = 0;
	while (end_choice != 1) {
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

		system("cls");
		end_choice = menu.getIndexChoice();
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
	
	Menu menu;
	makeMenu(menu);
	while (true) {
		switch (menu.getIndexChoice()) {
		case 0:
			std::cout << "Exiting program...\n";
			system("pause");
			return;
		case 1:
			runSingleTape();
			break;
		case 2:
			runMultiTape();
			break;
		case 3:
			runCompositions<SingleTapeTM>();
			break;
		case 4:
			runCompositions<MultitapeTM>();
			break;
		case 5:
			createMachine<SingleTapeTM>();
			break;
		case 6:
			createMachine<MultitapeTM>();
			break;
		default:
			return;
		}
	}
}