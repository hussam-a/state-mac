/*
Part of state-mac (github.com/hussam-a/state-mac)
Authors:
Hussam A. El-Araby (github.com/hussam-a)

Project code and configurations are under the GNU GPL license (state-mac/LICENSE) 
*/


//This class inherits from class action.
//It enables the construction and evaluation of expressions.

#ifndef expression_h
#define expression_h

#include <string>
using namespace std;

class state;

class expression : public action
{
	string sum, op1, op2;	//The entities that make an expression (sum = op1 + op2)

public:
	expression(string sum, string op1, string op2, state* parent, int typeNum); //Constructor
	expression(const expression* expressionToCopy);	//Copy constructor
	~expression();	//Destructor
	void act();	//Function that executes the action.
};

#endif
