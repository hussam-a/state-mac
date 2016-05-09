
//This is the class defines
//A base class for all actions
//It is inherited by all other sepcific derived classes of action (like sleep, wait, etc..)

#ifndef action_h
#define action_h

class state;

class action
{

	public:
		action(state* parent, int typeNum);	//Constructor
		action(const action* actionToCopy);	//Copy constructor
		virtual ~action();	//Virtual destructor
		virtual void act();	//Virtual act function that allows specifc at function of derived class to be called instead.
		state* parent;	//Pointer to the instance's parent state.
		int typeNum;	//A numeric variable indicating which type of action is this instance.
};

#endif
