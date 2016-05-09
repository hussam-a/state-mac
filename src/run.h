/*
Part of state-mac (github.com/hussam-a/state-mac)
Authors:
Hussam A. El-Araby (github.com/hussam-a)

Project code and configurations are under the GNU GPL license (state-mac/LICENSE) 
*/


//This class inherits from class action.
//It enables the FSM to call upon and run another FSM.

#ifndef run_h
#define run_h

#include <string>

class state;

class run : public action
{
	string whatToRun;		//Name of machine to run

public:
	run(string input, state* parent, int typeNum);	//Constructor
	run(const run* runToCopy);	//Copy constructor
	~run();	//Detructor
	void act();	//Function to execute the action
};

#endif
