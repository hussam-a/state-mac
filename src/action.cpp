/*
Part of state-mac (github.com/hussam-a/state-mac)
Authors:
Hussam A. El-Araby (github.com/hussam-a)

Project code and configurations are under the GNU GPL license (state-mac/LICENSE) 
*/

#include "simulation.h"
#include "action.h"
#include <iostream>
using namespace std;

action::action(state* parent, int typeNum) :parent(parent), typeNum(typeNum){}
action::~action(){}
action::action(const action* actionToCopy): parent(actionToCopy->parent), typeNum(actionToCopy->typeNum){}
void action::act(){}
