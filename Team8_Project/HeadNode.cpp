#include "HeadNode.h"

using namespace std;

Movie* HeadNode::latestMovieAddress = NULL;

/************************************************
Default constructor
Pre:
Post: calls getLineCount() to populate count member variable (# of entries)
	  pTree - dynamically allocate new BST of type 'Movie*'
	  pHash - dynamically allocate new BST of type 'Movie*'
	  arySize - Size of hash table
	  populateFromFile() populates structures 
Return:
************************************************/
HeadNode::HeadNode(){
	count = getLineCount();
	pTree = new BinNodeTree<Movie*>;
	pHash = new HashTable<string, Movie*>(count);
	arySize = pHash->getSize();
	pStack = new MovieStack;
	populateFromFile();//Populate BST, Hash Table,'count', and 'arySize' member variables
}

/************************************************
Destructor
Pre:
Post: deletes dynamically-allocated BST, Stack, and Hash Table
Return:
************************************************/
HeadNode::~HeadNode(){
	pTree->inorderTraversal(freeMovie);
	delete pTree;
	delete pStack;
	delete pHash;
}

/************************************************
Opens 'Movies.txt' and reads in data to populate structures
Pre:
Post:  BST and Hash Table will be populated with data from file
Return:
************************************************/
bool HeadNode::populateFromFile(){
	ifstream file("Movies.txt");

	if (!file.is_open()){//File could not be opened
		cout << "\tError: Movies.txt could not be opened" << endl;
		return false;
	}
	else{
		//Populate 'count' and 'arySize' member variables in 'HeadNode' class

		string data;
		string title, shortTitle, director, date;
		double gross;
		int runTime;
		stringstream ss;
		size_t next, last;
		Movie *movie;

		while (getline(file, data)){
			next = 0;
			last = 0;

			next = data.find(',', last);//Finds the position of ',' starting from the index last (in this case, last = 0)
			title = data.substr(last, next - last);//Split up string starting from index last (in this case 0), and get next-last amount of characters
			last = next + 2; //increment last (we increment by 2 to account for the comma and the space)

			next = data.find(',', last);
			shortTitle = data.substr(last, next - last);
			last = next + 2;

			next = data.find(',', last);
			ss.str(data.substr(last, next - last));
			ss >> gross;
			last = next + 2;
			ss.str(string());//Reset stringstream for next input
			ss.clear();

			next = data.find(',', last);
			director = data.substr(last, next - last);
			last = next + 2;

			next = data.find(',', last);
			date = data.substr(last, next - last);
			last = next + 2;

			ss.str(data.substr(last));
			ss >> runTime;
			ss.str(string());//Reset stringstream for next input
			ss.clear();

			movie = new Movie(title, shortTitle, gross, director, date, runTime);
			pTree->add(movie);//Add movie to tree
			pHash->add(movie);//Add movie to hash table
		}
		file.close();
		return true;
	}
}

/************************************************
Determines number of entries text file
Pre:
Post:
Return: int - number of lines in text file
************************************************/
int HeadNode::getLineCount(){
	ifstream file("Movies.txt");

	if (!file.is_open()){//File could not be opened
		cout << "\tError: Movies.txt file could not be opened" << endl;
		return -1;
	}

	string s;
	int count = 0;

	while (getline(file, s)){
		count++;
	}

	//Clear the EOF bit and move reading index back to beginning
	file.clear();
	file.seekg(0, ios::beg);

	file.close();

	return count;
}

/************************************************
Dislays contents of tree from biggest gross to smallest gross
Pre:
Post: contents of tree will be displayed inorder (right, root, left)
Return:
************************************************/
void HeadNode::displayTree(){
	pTree->biggestToSmallest(visit);
}

/************************************************
Displays horizontally indented tree 
Pre:
Post: tree is displayed
Return:
************************************************/
void HeadNode::displayIndentedTree(){
	pTree->printIndentedTree(visitAbbr);
}

/************************************************
Validates a user input by checking if it was not an int or is negative
Pre: T num - a double or an int
Post:
Return: bool - true if int is valid; false if it
************************************************/
template <class T>
bool HeadNode::validateNum(T num){
	if (cin.fail()){
		cin.clear();
		cin.ignore(100, '\n');
		cout << endl << "\tInvalid input received. Please try again.\n";
		return false;
	}

	if (num < 0){
		cout << endl << "\tPlease enter a positive number.\n";
		return false;
	}

	return true;
}

/************************************************
Validates date of format MM/DD/YY
Pre: std::string d - date to be validate
Post:
Return: bool - true is date is valid; false if date is invalid
************************************************/
bool HeadNode::validateDate(std::string d){
	//Format-MM/DD/YY
	int month, day, year;
	if (d.length() != 8 || d[2] != '/' || d[5] != '/'){
		cout << endl << "\tIncorrect format. Please try again.\n\t(Note: Single-digit values must be preceeded by a 0.)\n";
		return false;
	}

	stringstream ss;
	ss.str(d.substr(0, 2));
	ss >> month;
	ss.str(string());
	ss.clear();

	ss.str(d.substr(3, 2));
	ss >> day;
	ss.str(string());
	ss.clear();

	ss.str(d.substr(6, 2));
	ss >> year;

	if (month > 12 || month < 1){
		cout << endl << "\tInvalid month. Please try again.\n";
		return false;
	}
	if (year > 99 || year < 0){
		cout << endl << "\tInvalid year. Please try again.\n";
		return false;
	}
	if (day > 31 || year < 0){
		cout << endl << "\tInvalid day. Please try again.\n";
		return false;
	}

	return true;
}

/************************************************
Prompts user for input and adds to hash table
Pre: 
Post: BST and Hash Table contain new movie object
Return: 
************************************************/
void HeadNode::add(){
	string title, shortTitle, director, date;
	double gross;
	int runTime;
	bool cont = true;
	char ch;

	while (cont){
		cout << "\nEnter movie title: ";
		getline(cin, title);

		shortTitle = abbreviateTitle(title);

		do{
			cout << "\nEnter gross total in billions (Ex] 2.788): ";
			cin >> gross;
		} while (!validateNum(gross));

		cin.ignore(100, '\n');
		cout << "\nEnter movie director: ";
		getline(cin, director);

		do{
			cout << "\nEnter movie release date (Format-MM/DD/YY): ";
			getline(cin, date);
		} while (!validateDate(date));

		do{
			cout << "\nEnter movie runtime in minutes: ";
			cin >> runTime;
		} while (!validateNum(runTime));

		cin.ignore(100, '\n');

		cout << endl << endl;
		cout << "\tTitle: " << title << endl;
		cout << "\tGross: " << gross << " billion dollars" << endl;
		cout << "\tDirector: " << director << endl;
		cout << "\tDate: " << date << endl;
		cout << "\tRuntime: " << runTime << " minutes" << endl;
		cout << endl << endl;

		cout << "The following movie will be added to the database\n(Enter 'y' to confirm or 'n' to re-enter information): ";
		cin >> ch;
		cin.ignore(100, '\n');
		if (tolower(ch) == 'y'){
			Movie *movie = new Movie(title, shortTitle, gross, director, date, runTime);
			pTree->add(movie);//Add movie to tree
			pHash->add(movie);//Add movie to hash

			arySize = pHash->getSize();//If rehashing occured, update array size
			count++;
			cont = false;
			cout << endl << "\t\"" << movie->getTitle() << "\" successfully added to the database";
		}
	}
}

/************************************************
Returns abbreviated version of title
Pre: const string& title - title to be abbreviated
Post:
Return: std::string - abbreviated version of title
************************************************/
string HeadNode::abbreviateTitle(const string& title){
	string s = "";

	if (title.length() > 7){

		for (int i = 0; i < 5; i++){
			s += title[i];
		}

		s += "..";

		return s;
	}
	else{
		return title;
	}
}

/************************************************
Removes movie from bst
Pre:
Post: movie is removed from bst and added to undo stack (not freed from memory)
Return:
************************************************/
void HeadNode::remove(){
	string movieTitle;

	cout << "Enter movie title to remove: ";
	getline(cin, movieTitle);

	Movie* movieAddress = pHash->removeByString(movieTitle);//Find movie in hash and remove
	if (!movieAddress){
		cout << endl << "\tError: \"" << movieTitle << "\" was not found in the database." << endl << endl;
	}
	else{
		pTree->remove(removeAddress, movieAddress);//Static member 'latestMovieAddress' now contains address
		pStack->push(latestMovieAddress);
		count--;
		cout << endl << "\t\"" << movieAddress->getTitle() << "\" successfully removed from the database";
	}
}

/************************************************
Displays movie object in a formatted fashion
Pre: Movie* m - pointer a movie object to be displayed
Post: movie object is displayed to the screen
Return:
************************************************/
void HeadNode::displayMovie(Movie* m){
	cout << endl;
	cout << "\tTitle: " << m->getTitle() << endl;
	cout << "\tGross: " << m->getGross() << " billion dollars" << endl;
	cout << "\tDirector: " << m->getDirector() << endl;
	cout << "\tDate: " << m->getDate() << endl;
	cout << "\tRuntime: " << m->getRunTime() << " minutes" << endl;
}

/************************************************
Re-add's the top-most item in the undo stack to the BST and hash table
Pre:
Post: pop() is called on stack and movie address is added to BST and hash table
Return:
************************************************/
void HeadNode::undoDelete(){
	if (pStack->isEmpty()){
		cout << endl << "\tError: There are no deletes to undo" << endl;
		return;
	}
	else{
		Movie* m = pStack->pop();
		pTree->add(m);
		pHash->add(m);
		cout << endl << "\t\"" << m->getTitle() << "\" successfully re-added to the database";
	}
}

/************************************************
Displays hash table
Pre:
Post: movie objects in hash table displayed (title) in order of appearance
Return:
************************************************/
void HeadNode::displayHash(){
	pHash->displayTable();
}

/************************************************
Retreives and displays a movie, based on title, from the hash table
Pre:
Post: movie, if found, is displayed
Return:
************************************************/
void HeadNode::findByTitle(){
	string s;
	cout << endl << "Enter a movie title: ";
	getline(cin, s);

	Movie* m = pHash->findByString(s);
	if (m){
		displayMovie(m);
	}
	else{
		cout << "\n\tError: \"" << s << "\" not found in database." << endl;
	}
}

/************************************************
Compares two movies by gross and returns which made more 
Pre:
Post: Compares two movie classes and displays the difference in gross
Return:
************************************************/
void HeadNode::compare(){
	string m1, m2;
	Movie* movie1, *movie2;

	cout << endl << "Enter the first movie title: ";
	getline(cin, m1);

	movie1 = pHash->findByString(m1);

	while (!movie1){
		cout << "\n\tError: \"" << m1 << "\" not found in database. Please try again" << endl;
		cout << endl << "Enter the first movie title: ";
		getline(cin, m1);
		movie1 = pHash->findByString(m1);
	}

	cout << endl << "Enter the second movie title: ";
	getline(cin, m2);

	movie2 = pHash->findByString(m2);

	while (!movie2){
		cout << "\n\tError: \"" << m2 << "\" not found in database. Please try again" << endl;
		cout << endl << "Enter the second movie title: ";
		getline(cin, m2);
		movie2 = pHash->findByString(m2);
	}

	cout << endl;

	if (movie1->getGross() > movie2->getGross()){
		cout << "\t" << movie1->getTitle() << " made " << movie1->getGross() - movie2->getGross() << " billion more dollars than " << movie2->getTitle() << endl;
	}
	else{
		cout << "\t" << movie2->getTitle() << " made " << movie2->getGross() - movie1->getGross() << " billion more dollars than " << movie1->getTitle() << endl;
	}
}

/************************************************
Saves contents of current database to file and clears undo stack
Pre: 
Post: contents of hash table overwite current contents of "Movies.txt" and undo stack is cleared
Return:
************************************************/
void HeadNode::saveToFile(){
	char ch;

	cout << endl << "Note: Undo stack will be cleared. Continue? (Y/N): ";
	cin.get(ch);

	cin.ignore(100, '\n');

	if (tolower(ch) == 'y'){
		ofstream file("Movies.txt", ios::trunc);
		pHash->writeToFile(file);
		cout << endl << "\tDatabase successfully saved to 'Movies.txt'" << endl;
		file.close();
		pStack->clearMovieStack();
		return;
	}
	else{
		cout << endl;
		return;
	}
}

/************************************************
Exits main() and saves hash to 'Movies.txt'
Pre:
Post: main() loop will exit and hash table saved to file
Return:
************************************************/
void HeadNode::quitSave(){
	ofstream file("Movies.txt", ios::trunc);
	pHash->writeToFile(file);
	file.close();
	return;
}

/************************************************
Displays efficiency of various parts of program
Pre:
Post:
Return:
************************************************/
void HeadNode::efficiency(){
	cout << endl << "\tEfficiency for " << count << " movies" << endl;
	cout << "      " << setw(30) << setfill('_') << " " << setfill(' ') << endl << endl << fixed << setprecision(2);
	cout << setw(5) << " " << left << setw(25) << "\tNumber of collisions: " << setw(5) << pHash->getNumCollisions() << endl;
	cout << setw(5) << " " << left << setw(25) << "\tLongest Collision Path: " << pHash->getLongestCollision() << endl;
	cout << setw(5) << " " << left << setw(25) << "\tFill Factor: " << pHash->getFillFactor();
	cout << " (" << pHash->getCount() << " populated out of " << pHash->getSize() << " slots)" << endl;
	cout << setw(5) << " " << left << setw(25) << "\tPopulating: " << (pHash->getPopulateCount() + pTree->addCount) / static_cast<double>(count);
	cout << " (Hash: " << pHash->getPopulateCount() << " BST: " << pTree->addCount << ")" << endl;
	if (pTree->removeCount == 0){
		cout << setw(5) << " " << left << setw(25) << "\tRemove: " <<  "Please remove an item first" << endl;
	}
	else{
		cout << setw(5) << " " << left << setw(25) << "\tRemove: " << (pHash->getRemoveCount() + pTree->removeCount + 2) / static_cast<double>(count);
		//Add two to account for populating static variable and pushing to stack
	}
	cout << right;
};