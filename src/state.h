
//This class defines a state inside an FSM

#ifndef state_h
#define state_h

#include <vector>
#include <string>
#include "action.h"
using namespace std;

class machine;

class state
{
	vector <action*> actions;		//Vector containing the sequence of actions to be execute when this state is reached.
	action* createAction(string actionMandate);		//Function that creates an action (according to its own type)
	//And returns a pointer to the newly created data on the heap

public:
	state(string stateName, string stateContent, machine* parent);	//Constructor
	~state();	//Destructor
	state(const state& stateToCopy);	//Copy constructor
	void execute();	//Function to start executing the action vector one by one
	string stateName;	//Stores the state name (needed when a wait action sends to get a transition from the transition table)
	machine* parent;	//Stores a pointer to the parent machine containing this instance of class state
	bool stop;	//Stores the value which determines whether execution of state actions continues or not
	//For example, if a wait is executed and a transition occurs , this boolean makes sure this state is left and transtition
	//to next state is to be done by the machine freely.
};

#endif