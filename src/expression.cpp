
#include "simulation.h"
#include "expression.h"
#include <string>
using namespace std;

expression::expression(string sum, string op1, string op2, state* parent, int typeNum) : sum(sum), op1(op1), op2(op2), 
action(parent, typeNum) {}

expression::expression(const expression* expressionToCopy) : action(expressionToCopy), sum(expressionToCopy->sum)
, op1(expressionToCopy->op1), op2(expressionToCopy->op2) {}

expression::~expression(){};

void expression::act()
{
	bool flag;
	int value=0;
	int temp = parent->parent->getVal(op1, flag);
	if (flag)
		value = value + temp;
	else
		value = value + stoi (op1);

	temp = parent->parent->getVal(op2, flag);
	if (flag)
		value = value + temp;
	else
		value = value + stoi (op2);

	parent->parent->setVal(sum, value);

}