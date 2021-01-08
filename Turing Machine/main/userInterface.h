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

void removeSpaces(std::string& sentence) {
	sentence.erase(remove(sentence.begin(), sentence.end(), ' '), sentence.end());
}

void runSingleTape() {
	TuringMachine* tm = new SingleTapeTM();
	tm->loadMachine();
	if (tm->hasNoInstructions()) {
		std::cout << "Error in loading :(\n\n";
	}
	else {
		tm->usersTapeChoice();
		system("cls");
		tm->runMachine();
		delete tm;
	}
}

void runMultiTape() {
	std::string singletape_choice;
	TuringMachine* tm = new MultitapeTM();
	tm->loadMachine();
	if (tm->hasNoInstructions()) {
		std::cout << "Error in loading :(\n\n";
	}
	else {
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
		delete tm;
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

			
		}
		else if (command == "4") {

		}
		else {
			std::cout << "INVALID COMMAND!\n\n";
		}

	}
}