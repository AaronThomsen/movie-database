#ifndef MOVIE_H
#define MOVIE_H

#include <string>
#include <algorithm>
#include <iostream>
//Movie class
class Movie{
private:
	std::string title;
	std::string shortTitle;
	double gross;
	std::string director;
	std::string date;
	int runTime;
public:
	//Constructor
	Movie(std::string t, std::string sT, double g, std::string dir, std::string dat, int run) : title(t), shortTitle(sT), gross(g), director(dir), date(dat), runTime(run){
	}

	//Accessors
	std::string getTitle() const{
		return title;
	}
	std::string getShortTitle() const{
		return shortTitle;
	}
	double getGross() const{
		return gross;
	}
	std::string getDirector() const{
		return director;
	}
	std::string getDate() const{
		return date;
	}
	int getRunTime() const{
		return runTime;
	}

	//Mutators
	void setTitle(std::string t){
		title = t;
	}
	void setShortTitle(std::string t){
		shortTitle = t;
	}
	void setGross(double g){
		gross = g;
	}
	void setDirector(std::string d){
		director = d;
	}
	void setDate(std::string d){
		date = d;
	}
	void setRunTime(int r){
		runTime = r;
	}

	//BST overoaded operators
	bool operator <=(Movie* right);
	bool operator <(Movie* right);
	bool operator >(Movie* right);
	bool operator ==(Movie* right);
	bool operator ==(std::string s);
	bool operator <=(std::string s);
	bool operator ==(double d);
	bool operator <=(double d);
};

#endif