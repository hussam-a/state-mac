
#include "simulation.h"
#include "out.h"
#include <string>
#include <iostream>
using namespace std;

out::out(string whatToSay, state* parent, bool isExp, int typeNum) : action(parent, typeNum), isExp(isExp), whatToSay(whatToSay){}

out::~out(){}

out::out(const out* outToCopy) : action(outToCopy), isExp(outToCopy->isExp), whatToSay(outToCopy->whatToSay){}

void out::act()
{
	if (isExp)
	{
		bool flag;
		int temp = parent->parent->getVal(whatToSay, flag);
		if (flag)
			*(parent->parent->output) << temp << endl;
		else
			*(parent->parent->output) << whatToSay << endl;
	}
	else
		*(parent->parent->output) << whatToSay << endl;
}