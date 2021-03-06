/*
Part of state-mac (github.com/hussam-a/state-mac)
Authors:
Hussam A. El-Araby (github.com/hussam-a)

Project code and configurations are under the GNU GPL license (state-mac/LICENSE) 
*/


#include "simulation.h"
#include "wait.h"
#include <iostream>
using namespace std;

wait::wait(state* parent, int typeNum):action(parent, typeNum){}
wait::~wait(){}

wait::wait(const wait* waitToCopy) : action(waitToCopy){}

void wait::act()
{
	parent->parent->parent->inputMutex.lock();
	cout << parent->parent->machineName << ", input for transition: ";
	string input;
	cin >> input;
	parent->parent->parent->inputMutex.unlock();

	bool flag;
	string	stateToExecute = parent->parent->getTrans(parent->stateName, input, flag);
	if (flag)
	{
		parent->stop = true;
		parent->parent->nextState = stateToExecute;
	}
}
