// CIS 2362 Section 2165
// Final
//
// Author: Brown, Ryan
// SID: 5262
//
// Description:
// Restaurant Simulation - See the About section in the program.
//
// Output files will be created in program root directory as
// "logxxx.csv" and "statisticsxxx.dat".

#include "MainMenu.h"
#include <random>
#include <time.h>

int main(void){
	srand(time(NULL)); // Seed rand

	MainMenu::run(); // Run app

	return 0;

} // End main