/*
Part of state-mac (github.com/hussam-a/state-mac)
Authors:
Hussam A. El-Araby (github.com/hussam-a)

Project code and configurations are under the GNU GPL license (state-mac/LICENSE) 
*/


//This class defines an FSM

#ifndef machine_h
#define machine_h


#include <map>
#include <string>
#include <utility>
#include <fstream>
#include "state.h"
using namespace std;

//Structure transition holds important fields
struct transition{
	string toState;
	string fromState;
	string in;
};

class simulation;

class machine
{
	vector <transition> transitions;		//Vector of transitions available
	map <string, int> variables;		//Map of variable names and their values
	map <string, state> states;			//Map of state names and the state content of each state

public:

	machine(string file, simulation* parent, string machineName);	//Constructor
	machine(const machine& machineToCopy);	//Copy constructor
	~machine();	//Destructor
	void run();		//Function to run the machine.
	int getVal(string varName, bool& found);	//Function that returns a value when asked for it using its name.
	void setVal(string varName, int value);		//Function to set value of a certain variable.
	string getTrans(string fromStateName, string input, bool& found);	//Function to ask for the state to transit to.
	void executeState(string StateToExecute);	//Function that executes the next State
	string nextState;	//String that holds the next state to excute after the current one exits
	simulation* parent;	//Pointer to parent simulation of this FSM
	string machineName;	//String that holds the name of the machine
	bool stop;		//Boolean that stores whether to end the machine or not. for example when an end action is executed.
	ofstream* output;		//Holds the pointer for the output file.
};

#endif
