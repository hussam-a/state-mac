/*
Part of state-mac (github.com/hussam-a/state-mac)
Authors:
Hussam A. El-Araby (github.com/hussam-a)

Project code and configurations are under the GNU GPL license (state-mac/LICENSE) 
*/


//This is a global function that removes white space (spaces and new lines) from the start and end of a string.
//It works by going over the first and last characters of a string and only stops when both are
//characters not spaces.

#include <string>
using namespace std;

void remove_space(string& to_modify)
{
	bool flag = true;

	while (flag == true)
	{
		if (to_modify[0] == ' ' || to_modify[0] == '\n')
		{
			to_modify.erase(0, 1);
			flag = true;
		}
		else if (to_modify[to_modify.length() - 1] == ' ' || to_modify[to_modify.length() - 1] == '\n')
		{
			to_modify.erase(to_modify.length() - 1, 1);
			flag = true;
		}
		else
			flag = false;
	}
}
