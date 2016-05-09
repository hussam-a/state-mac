
#include "simulation.h"
#include "state.h"
#include "action.h"
#include "expression.h"
#include "out.h"
#include "run.h"
#include "sleep.h"
#include "endStatement.h"
#include "wait.h"
#include <string>

extern void remove_space(string& to_modify);

state::state(string stateName, string stateContent, machine* parent) :parent(parent), stateName(stateName), stop(false)
{
	int x = stateContent.find(",");
	while (true)
	{
		if (x == stateContent.npos)
			if (stateContent == "")
				break;

		string actionMandate = stateContent.substr(0, x);
		remove_space(actionMandate);
		
		actions.push_back(createAction(actionMandate));

		if (x == stateContent.npos)
			stateContent = "";
		else
			stateContent = stateContent.substr(x + 1);
		
		x = stateContent.find(",");
	}
}

state::~state()
{
	for (vector<action*>::iterator it = actions.begin(); it != actions.end(); ++it)
            delete((*it));
};

state::state(const state& stateToCopy) :parent(stateToCopy.parent), stateName(stateToCopy.stateName), stop(false)
{
	for (vector<action*>::const_iterator it = stateToCopy.actions.begin(); it != stateToCopy.actions.end(); ++it)
	{
		action* newAction;

		if ((*it)->typeNum == 1)
		{
			endStatement* newEnd = new endStatement(dynamic_cast<endStatement*>(*it));
			newAction = newEnd;
		}
		else if ((*it)->typeNum == 2)
		{
			expression* newExpression = new expression(dynamic_cast<expression*>(*it));
			newAction = newExpression;
		}
		else if ((*it)->typeNum == 3)
		{
			out* newOut = new out(dynamic_cast<out*>(*it));
			newAction = newOut;
		}
		else if ((*it)->typeNum == 4)
		{
			run* newRun = new run(dynamic_cast<run*>(*it));
			newAction = newRun;
		}
		else if ((*it)->typeNum == 5)
		{
			sleep* newSleep = new sleep(dynamic_cast<sleep*>(*it));
			newAction = newSleep;
		}
		else if ((*it)->typeNum == 6)
		{
			wait* newWait = new wait(dynamic_cast<wait*>(*it));
			newAction = newWait;
		}

		actions.push_back(newAction);
	}

	for (vector<action*>::iterator it = actions.begin(); it != actions.end(); ++it)
	{
		(*it)->parent = this;
	}
}

void state::execute()
{
	for (vector<action*>::iterator it = actions.begin(); it != actions.end(); ++it)
	{
		if (!stop)
		{
			(*it)->act();
		}
		else
		{
		    return;
	    }
	}
	stop = false;
}

action* state::createAction(string actionMandate)
{
	int x = actionMandate.find(" ");
	string key = actionMandate.substr(0, x);
	if (key == "out")
	{
		action* newOut;

        int y = actionMandate.find("\"");
		int z = actionMandate.find("\"", y + 1);

		if (y == actionMandate.npos || z == actionMandate.npos)
		{
			string whatToSay = actionMandate.substr(x+1);
			remove_space(whatToSay);
            newOut = new out(whatToSay, this, true, 3);
		}
		else
		{
	        string whatToSay = actionMandate.substr(y + 1, z - y - 1);
		    newOut = new out(whatToSay, this, false, 3);
	    }

		return newOut;
	}
	else if (key == "sleep")
	{
		action* newSleep = new sleep(actionMandate.substr(x + 1), this, 5);
		return newSleep;
	}
	else if (key == "wait")
	{
		action* newWait = new wait(this, 6);
		return newWait;
	}
	else if (key == "run")
	{
		action* newRun = new run(actionMandate.substr(x + 1), this, 4);
		return newRun;
	}
	else if (key == "end")
	{
		action* newEnd = new endStatement(this, 1);
		return newEnd;
	}
	else
	{
		x = actionMandate.find("=");
		string sum = actionMandate.substr(0, x);
		remove_space(sum);
		
		actionMandate = actionMandate.substr(x + 1);

		x = actionMandate.find("+");
		string op1 = actionMandate.substr(0, x);
		remove_space(op1);
		
		string op2 = actionMandate.substr(x + 1);
		remove_space(op2);
		
		action* newExpression = new expression(sum, op1, op2, this, 2);
		return newExpression;
	}
}