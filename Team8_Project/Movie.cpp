#include "Movie.h"

using namespace std;

//Overloaded operators for use in BST
bool Movie::operator <=(Movie* right){
	if (this->getGross() <= right->getGross()){
		return true;
	}
	else{
		return false;
	}
}

bool Movie::operator >(Movie* right){
	if (this->getGross() > right->getGross()){
		return true;
	}
	else{
		return false;
	}
}

bool Movie::operator <(Movie* right){
	if (this->getGross() < right->getGross()){
		return true;
	}
	else{
		return false;
	}
}


bool Movie::operator ==(double d){
	if (this->getGross() == d){
		return true;
	}
	else{
		return false;
	}
}

bool Movie::operator <=(double d){
	if (this->getGross() <= d){
		return true;
	}
	else{
		return false;
	}

}

bool Movie::operator ==(Movie* right){
	if (this->getGross() == right->getGross()){
		return true;
	}
	else{
		return false;
	}
}

bool Movie::operator ==(std::string s){
	string t1 = this->title;
	transform(t1.begin(), t1.end(), t1.begin(), ::toupper);
	transform(s.begin(), s.end(), s.begin(), ::toupper);
	if (t1 == s){
		return true;
	}
	else{
		return false;
	}
}


bool Movie::operator <=(std::string s){
	string t1 = this->title;
	transform(t1.begin(), t1.end(), t1.begin(), ::toupper);
	transform(s.begin(), s.end(), s.begin(), ::toupper);
	if (t1 <= s){
		return true;
	}
	else{
		return false;
	}
}