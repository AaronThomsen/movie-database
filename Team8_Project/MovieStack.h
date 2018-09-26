#ifndef MOVIESTACK_H
#define MOVIESTACK_H

#include "Stack.h"
#include "Movie.h"

//MovieStack class (Undo stack for movies)
class MovieStack : public Stack<Movie*>{
public:
	//Destructor
	~MovieStack(){
		clearMovieStack();
	}

	//Releases all movie objects stored in stack
	//when called
	void clearMovieStack(){
		int i = this->getCount();
		Movie *temp;

		for (; i != 0; i--){
			temp = this->pop();
			delete temp;
		}
	}
};
#endif