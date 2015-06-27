#ifndef H_PATRONGROUP
#define H_PATRONGROUP
#pragma once

// PatronGroup
// Description: A group of patrons visiting the Restaurant
class PatronGroup
{
public:
	// Constructors
	PatronGroup(void);
	PatronGroup(int, int, int); // Id, number patrons, target dining time
	~PatronGroup(void);

	// Time manipulators
	void advanceWaitTime(void);
	void advanceDiningTime(void);
	void addToDiningTime(int);

	// Set methods
	void setDiningTime(int);
	void setWaiterTime(int t){if(t > 0) waiterTime = t;};

	// Get methods
	bool isFinished(void){return finished;};
	int getTotalTime(void){return totalTime;};
	int getTotalWaitTime(void){return waitTime;};
	int getTotalDiningTime(void){return diningTime + waiterTime;};
	int getId(void){return id;};

private:
	int id; // Unique ID
	int numberPatrons; // Number of patrons for group

	int totalTime; // Total time at restaurant
	int waitTime; // Total time waiting in line
	int diningTime; // Total time dining
	int targetDiningTime; // Time patrons will be dining
	int waiterTime; // Time added by waiter

	bool finished; // True if group is finished

	void writeToLog(void); // Writes PatronGroup data to logfile on leave

}; // End PatronGroup

#endif
