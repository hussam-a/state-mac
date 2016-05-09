
#include "simulation.h"
#include "sleep.h"
#include <windows.h>
#include <string>
using namespace std;

sleep::sleep(string howMuchToSleep, state* parent, int typeNum) : action(parent, typeNum), howMuchToSleep(stoi (howMuchToSleep)){}

sleep::~sleep(){}

sleep::sleep(const sleep* sleepToCopy) : action(sleepToCopy), howMuchToSleep(sleepToCopy->howMuchToSleep) {}

void sleep::act()
{
	Sleep(howMuchToSleep*1000);
}