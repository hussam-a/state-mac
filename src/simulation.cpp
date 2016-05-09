
#include "simulation.h"
#include <fstream>
#include <map>
#include <string>
#include <utility>
#include <mutex>
#include <thread>
#include <iostream>
using namespace std;

extern void remove_space(string& to_modify);

simulation::simulation():mutexIndex(-1){}

simulation::~simulation(){};

void simulation::parse(string machineName)
{
	string machineFileName = machineName + ".fsm";
	map <string, machine>::iterator it = machine_table.find(machineName);
	if (it == machine_table.end())
	{
		ifstream machineFile(machineFileName);
		if (machineFile.is_open())
		{
			string file = "";
			char c;
			machineFile.get(c);
			while (!machineFile.eof())
			{
				file = file + c;
				machineFile.get(c);
			}
			machineFile.close();

			machine newMachine(file, this, machineName);
			machine_table.insert(make_pair(machineName, newMachine));
		}
	}
}

int simulation::getVal(string varName, bool& found)
{
	int num;
	map <string, variable>::iterator it = commonVars.find(varName);
	if (it == commonVars.end())
	{
		found = false;
		num = -1;
	}
	else
	{
		mutexList[it->second.mutexIndex].lock();
		num = it->second.value;
		mutexList[it->second.mutexIndex].unlock();
		found = true;
	}
	return num;
}

void simulation::setVal(string varName, int value)
{
	map <string, variable>::iterator it = commonVars.find(varName);
	if (it != commonVars.end())
	{
		mutexList[it->second.mutexIndex].lock();
		it->second.value = value;
		mutexList[it->second.mutexIndex].unlock();
	}
}

void simulation::setup(string mFSMFileName)
{
	ifstream mFSMFile(mFSMFileName);
	if (mFSMFile.is_open())
	{
		string file = "";
		char c;
		mFSMFile.get(c);
		while (!mFSMFile.eof())
		{
			file = file + c;
			mFSMFile.get(c);
		}
		mFSMFile.close();

		int x = file.find("MFSM");
		
		if (x != file.npos)
		{
			file = file.substr(file.find("\n"));
			x = file.find("COMVAR");
			file = file.substr(x+6);
			x = file.find("machines:");
			string myVars = file.substr(0, x);
			remove_space(myVars);
			string myMachs = file.substr(x + 9);
			remove_space(myMachs);
			
			x = myVars.find(",");
			while (true)
			{
				if (x == myVars.npos)
					if (myVars == "")
						break;

				string varName = myVars.substr(0, x);
				remove_space(varName);
				
				commonVars.insert(pair<string, variable>(varName, variable(0, ++mutexIndex)));

				if (x == myVars.npos)
					myVars = "";
				else
					myVars = myVars.substr(x + 1);

				x = myVars.find(",");
			}

			x = myMachs.find("\n");
			while (true)
			{
				string machineName;
				if (x == myMachs.npos)
				{
					if (myMachs == "")
					{
						break;
					}
					else
					{
						machineName = myMachs;
						remove_space(machineName);
					}
				}
				else
				{
					machineName = myMachs.substr(0, x);
					remove_space(machineName);
				}

				machineList.push_back(machineName);

				if (x == myVars.npos)
					myMachs = "";
				else
				{
					myMachs = myMachs.substr(x + 1);
					x = myMachs.find("\n");
				}
			}


		}
		else
			return;
	}
	else
		return;

	for (vector<string>::iterator it = machineList.begin(); it != machineList.end(); ++it)
	{
		string machineName = (*it);
		this->parse(machineName);
	}
}

void simulation::run()
{
	for (vector<string>::iterator it = machineList.begin(); it != machineList.end(); ++it)
	{
		map <string, machine>::iterator iu = machine_table.find((*it));
		threadList.emplace_back(&machine::run, (iu->second));
	}

	for (thread& i : threadList)
		i.join();


	for (vector<string>::iterator it = machineList.begin(); it != machineList.end(); ++it)
	{
		map <string, machine>::iterator iu = machine_table.find((*it));
		iu->second.output->close();
	}
}