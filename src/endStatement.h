/*
Part of state-mac (github.com/hussam-a/state-mac)
Authors:
Hussam A. El-Araby (github.com/hussam-a)

Project code and configurations are under the GNU GPL license (state-mac/LICENSE) 
*/


//This class inherits from class action
//It enables the stopping of an FSM when called.

#ifndef endStatement_h
#define endStatement_h

class state;

class endStatement : public action
{
public:
	endStatement(state* parent, int typeNum);	//Constructor
	endStatement(const endStatement* endStatementToCopy);	//Copy constructor
	~endStatement();	//Destructor
	void act();		//The act function executes the action.
};


#endif
