
//This class define the simulation (most top level class).

#ifndef simulation_h
#define simulation_h

#include "machine.h"
#include <map>
#include <vector>
#include <string>
#include <mutex>
#include <thread>
using namespace std;

class variable		//Class defining a variable. each variable has a value and a mutex index
{
public:
	variable(int value, int mutexIndex) :value(value), mutexIndex(mutexIndex){};
	~variable(){};
	int value;
	int mutexIndex;
};

class simulation
{

	int mutexIndex;	//Index to give each varibale a unique mutex
	map <string, variable> commonVars;	//Map to hold common variables
	mutex mutexList [1000];		//Array of mutex required for locking the threads
	
	vector <string>  machineList;	//Vector holding list of machine names.
	vector <thread> threadList;		//vector holding the threads spawned.

	public:
		simulation();	//Constructor
		~simulation();	//Destructor
		void setup(string mFSMFileName);
		int getVal(string varName, bool& found);
		void setVal(string varName, int value);
		void run();
		void parse(string machineName);	//Function that starts parsing of a certain machine.
		map <string, machine> machine_table;	//Map to hold the different machines simulated up to the moment (name, machine)
		//helps save time to avoid reparsing the machine everytime if it is called more than once.
		mutex inputMutex;	//Global mutex for all machine to synchronise the input process
};

#endif