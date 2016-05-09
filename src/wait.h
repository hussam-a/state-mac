
//This class inherits from class action.
//It enables the user to input a number to indicate a certain transition.

#ifndef wait_h
#define wait_h

class state;

class wait : public action
{
public:
	wait(state* parent, int typeNum);	//Constructor
	wait(const wait* waitToCopy);	//Copy constructor
	~wait();	//Destructor
	void act();	//Function to execute action
};


#endif