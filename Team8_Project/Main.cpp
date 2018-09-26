/*********************************************
Team 8 (Movie Database)
-----------------------
Members:
	Aaron Thomsen
	Roy Sumida
	Quentin Monasterial
	Lam Nguyen
*********************************************/
#include "HeadNode.h"

using namespace std;

int getUserChoice();
void executeChoice(int choice, HeadNode &h, bool &q);


int main(){
	cout << "\t\tWelcome to the movie database!" << endl;
	cout << setfill('_') << setw(80) << " " << endl << setfill(' ');

	HeadNode h;
	bool quit = false;
	int choice;

	while (!quit){
		choice = getUserChoice();
		executeChoice(choice, h, quit);
	}
}

/************************************************
Gets a valid user choice after displaying the menu options
Pre:
Post:
Return: int - a number on [1, 11] representing the user's choice
************************************************/
int getUserChoice(){
	int choice;

	cout << endl << endl;
	cout << setw(25) << "--Menu--" << endl << endl;
	cout << "  1. Add new movie" << endl;
	cout << "  2. Delete movie" << endl;
	cout << "  3. Undo delete" << endl;
	cout << "  4. Search for movie by Title" << endl;
	cout << "  5. Display movies in hash table" << endl;
	cout << "  6. Display movies by gross" << endl;
	cout << "  7. Display movies in indented tree" << endl;
	cout << "  8. Efficiency" << endl;
	cout << "  9. Compare two movies by gross total" << endl;
	cout << "  10. Save current database to file" << endl;
	cout << "  11. Quit" << endl;
	cout << endl << "Enter an option: ";

	while (!(cin >> choice) || (choice < 1 || choice > 11)){
		cin.clear();
		cin.ignore(1000, '\n');
		cout << endl << "Please enter a valid integer: ";
	}

	cin.ignore(1000, '\n');
	cout << endl;
	return choice;
}

/************************************************
Executes a command based on the user's input
Pre: int choice - the user's choice
	 HeadNode &h - a headNode object 
	 bool &q - a boolean representing if the user wants to quit
Post: appropriate headnode function will be executed
Return:
************************************************/
void executeChoice(int choice, HeadNode &h, bool &q){
	switch (choice){
	case 1:
		h.add();
		break;
	case 2:
		h.remove();
		break;
	case 3:
		h.undoDelete();
		break;
	case 4:
		h.findByTitle();
		break;
	case 5:
		h.displayHash();
		break;
	case 6:
		h.displayTree();
		break;
	case 7:
		h.displayIndentedTree();
		break;
	case 8:
		h.efficiency();
		break;
	case 9:
		h.compare();
		break;
	case 10:
		h.saveToFile();
		break;
	case 11:
		h.quitSave();
		q = true;
		break;
	}
}