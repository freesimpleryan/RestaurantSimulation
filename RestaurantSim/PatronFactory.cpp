#include "PatronFactory.h"
#include <algorithm>
#include <random>
#include <iostream>
#include <time.h>

// Initialize static variables
int PatronFactory::idCounter = 0;
int PatronFactory::defaultMin = 1;
int PatronFactory::defaultMax = 1;
int PatronFactory::currentMin = defaultMin;
int PatronFactory::currentMax = defaultMax;
int PatronFactory::maxTargetDiningTime = 0;
int PatronFactory::maxTargetDiningTimeSingle = 0;
int PatronFactory::minTargetDiningTime = 0;
int PatronFactory::minTargetDiningTimeSingle = 0;

// newPatronGroup
// Description: Generates a new randomly generated PatronGroup
PatronGroup PatronFactory::newPatronGroup(){

	idCounter++; // Get new ID
	int numberPatrons = rand() % currentMax + currentMin; // Pool number of patrons

	// Pool target dining time
	int targetDiningTime;
	if(numberPatrons == 1){
		targetDiningTime = rand() % maxTargetDiningTimeSingle + minTargetDiningTimeSingle;
	}
	else{
		targetDiningTime = rand() % maxTargetDiningTime + minTargetDiningTime;
	}
	
	return PatronGroup(idCounter, numberPatrons, targetDiningTime);

} // End newPatronGroup



// setRestaurantType
// Description: Uses the restaurant type to setup other variables
// in the class based on the design specifications.
void PatronFactory::setRestaurantType(string t){

	transform(t.begin(), t.end(), t.begin(), toupper);

	if(t == "DINER"){
		minTargetDiningTime = 15;
		maxTargetDiningTime = 60;
		minTargetDiningTimeSingle = 5;
		maxTargetDiningTimeSingle = 45;
	}
	else if(t == "CASUAL"){
		minTargetDiningTime = 45;
		maxTargetDiningTime = 90;
		minTargetDiningTimeSingle = 15;
		maxTargetDiningTimeSingle = 60;
	}
	else if(t == "GOURMET"){
		minTargetDiningTime = 60;
		maxTargetDiningTime = 120;
		minTargetDiningTimeSingle = 45;
		maxTargetDiningTimeSingle = 90;
	}
	else{
		minTargetDiningTime = 0;
		maxTargetDiningTime = 0;
		minTargetDiningTimeSingle = 0;
		maxTargetDiningTimeSingle = 0;
	}

} // End setRestaurantType



// The following methods set min, max, defaults, etc.
void PatronFactory::setMin(int m){
	if(m >= 0 && m <= currentMax)
		currentMin = m;
} // End setMin

void PatronFactory::setMax(int m){
	if(m >= 0 && m >= currentMin)
		currentMax = m;
} // End setMax

void PatronFactory::setDefaultMinMax(int min, int max){
	if(min <= max && min >=0){
		defaultMin = min;
		defaultMax = max;
	}
} // End setDefaultMinMax

void PatronFactory::setMinMax(int min, int max){
	if(min <= max && min >=0){
		currentMin = min;
		currentMax = max;
	}
} // End setMinMax

void PatronFactory::resetMinMax(void){
	currentMin = defaultMin;
	currentMax = defaultMax;
} // end resetMinMax
