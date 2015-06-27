#include "PatronGroup.h"
#include "TimeStamp.h"
#include "Waiter.h"

#include <fstream>
#include <iostream>


using namespace std;

// Default Constructor
// Description: Used to mark a PatronGroup as finished
PatronGroup::PatronGroup(void)
{
	id = 0;
	numberPatrons = 0;
	targetDiningTime = 0;

	totalTime = 0;
	waitTime = 0;
	diningTime = 0;
	
	waiterTime = 0;
	finished = true;
} // End Default Constructor


// 3 Call Constructor
// Description: Sets a Patron Group (used by factory)
PatronGroup::PatronGroup(int i, int n, int t){
	id = i;
	numberPatrons = n;
	targetDiningTime = t;

	totalTime = 0;
	waitTime = 0;
	diningTime = 0;

	waiterTime = 0;
	finished = false;
} // End 3 Call Constructor


// Destructor
PatronGroup::~PatronGroup(void){} // End Destructor



// setDiningTime
// Description: Sets the PatronGroup's dining time
void PatronGroup::setDiningTime(int t){
	if(t > 0){
		diningTime = t;
	}
	if(diningTime >= targetDiningTime){ // Check if finished dining
		finished = true;
		writeToLog();
	}
} // End setDiningTime


// advanceWaitTime
// Description: Incremements a PatronGroup's waitTime by one.
void PatronGroup::advanceWaitTime(void){waitTime++;} // End advanceWaitTime



// advanceDiningTime
// Description: Increments a PatronGroup's diningTime by one.
void PatronGroup::advanceDiningTime(void){
	diningTime++;
	if(diningTime >= targetDiningTime){ // Check if finished.
		finished = true;
		writeToLog();
	}
} // End advanceDiningTime



// addToDiningTime
// Description: Adds a value to a PatronGroup's diningTime
void PatronGroup::addToDiningTime(int t){
	if(t > 0){
		diningTime += t;
	}
	if(diningTime >= targetDiningTime){ // Check if finished
		finished = true;
		writeToLog();
	}
} // End addToDiningTime



// writeToLog
// Description: Called when a PatronGroup leaves, writes data to a
// log file for the session.
void PatronGroup::writeToLog(void){

	string filePath = "log" + TimeStamp::get() + ".csv";

	// Add in waiter time
	waiterTime = Waiter::getTime(numberPatrons);
	diningTime += waiterTime;
	totalTime = diningTime + waitTime;
	
	// Write to csv file
	ofstream output;
	output.open(filePath, ofstream::app);
	output << id << ";" <<
		numberPatrons << ";" <<
		totalTime << ";" <<
		waitTime << ";" <<
		diningTime << ";" <<
		targetDiningTime << ";" <<
		waiterTime << ";\n";

	output.close();
} // End writeToLog
