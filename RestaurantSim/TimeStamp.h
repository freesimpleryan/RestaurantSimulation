#ifndef H_TIMESTAMP
#define H_TIMESTAMP
#pragma once

#include <string>

using namespace std;

// TimeStamp
// Description: Generates a random number to use as a file
// timestamp.
class TimeStamp
{
public:
	// Constructor/deconstructor
	TimeStamp(void);
	~TimeStamp(void);

	static string get(void);
	static void set(void); // Generates timestamp

private:
	static string dateTime; // Holds timestamp

}; // End TimeStamp

#endif
