# state-mac
Multi Finite State Machine Simulator 

Threads based.

Authors:

Hussam A. El-Araby (github.com/hussam-a)

Project code and configurations are under the GNU GPL license (state-mac/LICENSE)

# Project structure:

- C++ source code to compile (state-mac/src)

#Guidelines

- To compile
  * Use every single .h and .cpp in the compilation process
  * Run the produced .exe

- To use
  * When first run, you will be asked about the file name of the Multi FSM machine you need to run.
  * It will be parsed and its included FSM machines too.
  * After that, you will be asked about which state in each FSM do you want to start at.
  * Then the process would switch between all threads of all the active FSMs till all end and threads join at the end.
  * When a transition input is required from the user, the user will be prompted for it.
  * Output is in a seperate file (with the same name as each FSM + ".out")
  * The simulation only ends when all FSMs end.

- Notes:
  * Data races are prevented by the use of mutex locks when accessing the variables.
  * Also a mutex lock is used to synchronise the input process.
