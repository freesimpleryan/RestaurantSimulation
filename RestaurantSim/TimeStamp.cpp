#include "TimeStamp.h"
#include <random>

string TimeStamp::dateTime = ""; // Holds DateTime value

// Default Constructor/Deconstructor
TimeStamp::TimeStamp(void){}
TimeStamp::~TimeStamp(void){}
// End Default Constructor/Deconstructor


// set
// Description: Sets a random number for the timestamp. Used
// for file naming.
void TimeStamp::set(void){dateTime = to_string(rand() % 9000000 + 1);} // End set


// get
// Description: Returns timestamp.
string TimeStamp::get(void){return dateTime;} // End get
