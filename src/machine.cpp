
#include "simulation.h"
#include "machine.h"
#include <utility>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

extern void remove_space(string& to_modify);

machine::machine(string file, simulation* parent, string machineName) : parent(parent), stop(false), machineName(machineName)
{
	string outputFileName = machineName + ".out";
	output = new ofstream(outputFileName);
	if (output->is_open())
	{
		int x = file.find("VAR");
		file = file.substr(x + 3);

		x = file.find("States:");
		string myVars = file.substr(0, x);
		file = file.substr(x + 7);

		x = file.find("Transitions:");
		string myStates = file.substr(0, x);

		string myTrans = file.substr(x + 12);

		x = myVars.find(",");
		while (true)
		{
			if (x == myVars.npos)
				if (myVars == "")
					break;

			string varName = myVars.substr(0, x);
			remove_space(varName);
			bool found;
			int v = parent->getVal(varName, found);
			if (!found)
			{
				variables.insert(pair<string, int>(varName, 0));
			}

			if (x == myVars.npos)
				myVars = "";
			else
				myVars = myVars.substr(x + 1);

			x = myVars.find(",");
		}

		x = myStates.find(":");
		while (true)
		{
			if (x == myStates.npos)
				if (myStates == "")
					break;

			string stateName = myStates.substr(0, x);
			remove_space(stateName);

			myStates = myStates.substr(x + 1);

			int y = myStates.find("\n");
			string stateContent;
			if (y == myStates.npos)
				stateContent = myStates;
			else
				stateContent = myStates.substr(0, y);
			remove_space(stateContent);

			states.insert(pair<string, state>(stateName, state(stateName, stateContent, this)));

			if (x == myVars.npos)
				myStates = "";
			else
			{
				myStates = myStates.substr(y + 1);
				x = myStates.find(":");
			}
		}

		x = myTrans.find(",");
		while (true)
		{
			if (x == myTrans.npos)
				if (myTrans == "")
					break;

			string a = myTrans.substr(0, x);
			remove_space(a);

			myTrans = myTrans.substr(x + 1);

			int y = myTrans.find(",");
			string b = myTrans.substr(0, y);
			remove_space(b);

			myTrans = myTrans.substr(y + 1);

			x = myTrans.find("\n");
			if (y == myTrans.npos)
				y = myTrans.length();
			string in = myTrans.substr(0, y);
			remove_space(in);

			transition toPush;
			toPush.fromState = a;
			toPush.toState = b;
			toPush.in = in;

			transitions.push_back(toPush);

			if (x == myTrans.npos)
				myTrans = "";
			else
			{
				myTrans = myTrans.substr(x + 1);
				x = myTrans.find(",");
			}
		}
	}
}

machine::~machine(){};

machine::machine(const machine& machineToCopy) : parent(machineToCopy.parent), stop(false),
transitions(machineToCopy.transitions), states(machineToCopy.states), variables(machineToCopy.variables),
machineName(machineToCopy.machineName), output(machineToCopy.output)
{
	for (map <string, state>::iterator it = states.begin(); it != states.end(); ++it)
		it->second.parent = this;
}

void machine::run()
{
	parent->inputMutex.lock();
    cout << machineName << ", start at state: ";
	cin >> nextState;
	cout << endl;
	parent->inputMutex.unlock();
	while (!stop)
	{
		executeState(nextState);
	}
	stop = false;
}

int machine::getVal(string varName, bool& found)
{
	bool commFound;
	int v = parent->getVal(varName, commFound);
	if (commFound)
	{
		found = true;
		return v;
	}
	else
	{
		map <string, int>::iterator it = variables.find(varName);
		if (it == variables.end())
		{
			found = false;
			return v;
		}
		else
		{
			found = true;
			return it->second;
		}
	}
}

void machine::setVal(string varName, int value)
{
	bool commFound;
	int v = parent->getVal(varName, commFound);
	if (commFound)
	{
		parent->setVal(varName, value);
	}
	else
	{
		map <string, int>::iterator it = variables.find(varName);
		if (it != variables.end())
			it->second = value;
	}
}

string machine::getTrans(string fromStateName, string input, bool& found)
{
	vector<transition>::iterator itx = transitions.end();

	for (vector<transition>::iterator it = transitions.begin(); it != transitions.end(); ++it)
	{
		if (it->fromState == fromStateName)
			if (it->in == input)
				itx = it;
	}

	if (itx == transitions.end())
	{
		found = false;
		return "";
	}
	else
	{
		found = true;
		return itx->toState;
	}
}

void machine::executeState(string stateName)
{
	map <string, state>::iterator it = states.find(stateName);
	if (it != states.end())
		it->second.execute();
}