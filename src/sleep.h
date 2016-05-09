/*
Part of state-mac (github.com/hussam-a/state-mac)
Authors:
Hussam A. El-Araby (github.com/hussam-a)

Project code and configurations are under the GNU GPL license (state-mac/LICENSE) 
*/


//This class inherits from class action.
//It enables the FSM to sleep for "x" seconds.

#ifndef sleep_h
#define sleep_h

#include <string>
class state;

class sleep : public action
{
	int howMuchToSleep;	//How many seconds to sleep?

public:
	sleep(string howMuchToSleep, state* parent, int typeNum);	//Constructor
	sleep(const sleep* sleepToCopy);	//Copy constructor
	~sleep();	//Destructor
	void act();		//Function to execute the action
};

#endif
