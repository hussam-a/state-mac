
#include <crtdbg.h>
#include <errno.h>
#include <iostream>
#include <string>
#include "simulation.h"
using namespace std;

int main()
{
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_WNDW);

	cout << "Enter multi FSM file name: ";
	string mFSMFileName;
	cin >> mFSMFileName;
	simulation newSimulation;
	newSimulation.setup(mFSMFileName);
	newSimulation.run();
	cout << endl;
	system("pause");
	return 0;
}