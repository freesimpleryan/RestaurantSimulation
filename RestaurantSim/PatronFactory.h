#ifndef H_PATRONFACTORY
#define H_PATRONFACTORY
#pragma once

#include "PatronGroup.h"
#include <string>

using namespace std;

// PatronFactory
// Description: Handles generating new PatronGroups based
// on set parameters
class PatronFactory
{
public:
	PatronFactory(void){};
	~PatronFactory(void){};

	static PatronGroup newPatronGroup(void); // Primary method call to generate PatronGroup

	// Set methods
	static void setRestaurantType(string);
	static void setMin(int);
	static void setMax(int);
	static void setMinMax(int, int);
	static void setDefaultMinMax(int, int);

	static void resetMinMax(void); // Resets the min/max to defaults

private:
	static int defaultMin; // Default minimum patrons per group
	static int defaultMax; // Default max patrons per group
	static int currentMin; // Current minimum patrons per group
	static int currentMax; // Current max patrons per group

	// Target dining time - Time a PatronGroup will leave the restaurant
	static int minTargetDiningTime;
	static int maxTargetDiningTime;
	// For groups of 1
	static int minTargetDiningTimeSingle;
	static int maxTargetDiningTimeSingle;

	static int idCounter; // Assigns unique ID for each group

}; // End PatronFactory

#endif
