
//This class inherits from class action.
//It enables the statement/expression to be output on the screen

#ifndef out_h
#define out_h


class state;

class out: public action
{
	string whatToSay;	//Store what to ouput
	bool isExp;		//Determines whether it is an expression (it's value would be derived from the variables table, or not
	//just output whatToSay on the screen

	public:
		out(string whatToSay, state* parent, bool isExp, int typeNum);	//Constructor
		out(const out* outToCopy);	//Copy constructor
		~out();	//Destructor
		void act();	//Function to execute the action.
};

#endif