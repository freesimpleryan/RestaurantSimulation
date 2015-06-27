#ifndef H_WAITER
#define H_WAITER
#pragma once

#include <algorithm>
#include <string>
#include <random>
#include <time.h>
using namespace std;

// Waiter
// Description: Adds time for wait staff
class Waiter
{
public:
	// Constructor
	Waiter(void){};
	~Waiter(void){};

	// getTime
	// Description: Returns a random amount of time for the
	// wait staff per the skill level.
	static int getTime(int p){
		return p * (rand() % maxTime + minTime);
	}; // End getTime

	// setSkillLevel
	// Description: Sets the wait staff skill level.
	static void setSkillLevel(string skill){
		transform(skill.begin(), skill.end(), skill.begin(), toupper);
		if(skill == "NEW_HIRE"){
			minTime = 5;
			maxTime = 5;
		}
		else if(skill == "SEASONED"){
			minTime = 3;
			maxTime = 5;
		}
		else if(skill == "PROFESSIONAL"){
			minTime = 1;
			maxTime = 2;
		}
	}; // End setSkillLevel

private:
	static int minTime; // Minimum time to add per patron
	static int maxTime; // Maximum time to add per patron
}; // End Waiter

#endif
