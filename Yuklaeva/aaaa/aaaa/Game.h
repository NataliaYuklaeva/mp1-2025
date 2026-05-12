#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <cmath>
#include <string>
#include "class_Vector_Matrix.h"

using namespace std;

class Gamer {
protected:
	string name;
	Matrix range;
public:
	Gamer(const string& n = "Gamer.0") : name(n) {}
	virtual ~Gamer() {}

	virtual void Do() = 0;
	virtual void Answer() = 0;
};

class User :public Gamer {

};
