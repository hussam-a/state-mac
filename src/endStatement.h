
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