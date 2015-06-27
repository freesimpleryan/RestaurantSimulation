#ifndef H_TABLE
#define H_TABLE
#pragma once

#include "PatronGroup.h"

// Table
// Description: A table at the restaurant
class Table
{
public:
	// Constructors
	Table(){};
	Table(int); // Set size
	~Table(void);

	PatronGroup& getPatronGroup(void); // PatronGroup accessor
	void seatPatronGroup(PatronGroup); // Seat PatronGroup at table
	bool isAvailable(void); // Return true if table is available
	void removePatronGroup(void); // Set the PatronGroup to default (ID = 0)

private:
	int size; // Size of table
	bool available; // True if table is available/PatronGroup is finished
	PatronGroup patrons; // PatronGroup at table

}; // End Table

#endif
