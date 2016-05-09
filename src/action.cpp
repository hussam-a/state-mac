
#include "simulation.h"
#include "action.h"
#include <iostream>
using namespace std;

action::action(state* parent, int typeNum) :parent(parent), typeNum(typeNum){}
action::~action(){}
action::action(const action* actionToCopy): parent(actionToCopy->parent), typeNum(actionToCopy->typeNum){}
void action::act(){}