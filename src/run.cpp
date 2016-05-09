
#include "simulation.h"
#include "run.h"
#include <string>
using namespace std;

run::run(string input, state* parent, int typeNum) : action(parent, typeNum)
{
	whatToRun = input + ".fsm";
}
run::~run(){};

run::run(const run* runToCopy) : action(runToCopy), whatToRun(runToCopy->whatToRun){}

void run::act()
{
	parent->parent->parent->parse(whatToRun);
	map <string, machine>::iterator it = parent->parent->parent->machine_table.find(whatToRun);
	it->second.run();
}