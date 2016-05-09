
#include "simulation.h"
#include "endStatement.h"
using namespace std;

endStatement::endStatement(state* parent, int typeNum) : action(parent, typeNum) {}

endStatement::endStatement(const endStatement* endStatementToCopy): action(endStatementToCopy) {}

endStatement::~endStatement(){}

void endStatement::act()
{
	parent->stop = true;
	parent->parent->stop = true;
}