#include "Table.h"


// Constructor - Sets a available table with an empty PatronGroup
// at the specified size.
Table::Table(int s)
{
	if(s > 0)
		size = s;
	patrons = PatronGroup();
	available = true;
} // End Constructor

// Desctructor
Table::~Table(void){} // End Destructor

// getPatronGroup
// Description: Exposes PatronGroup for the Table
PatronGroup& Table::getPatronGroup(void){return patrons;} // End getPatronGroup


// seatPatronGroup
// Description: Sets the patrons to the given PatronGroup
void Table::seatPatronGroup(PatronGroup p){
	patrons = p;
	available = false;
} // End seatPatronGroup

// isAvailable
// Description: Resturns if the table is available to be bussed.
bool Table::isAvailable(void){return available;} // End isAvailable


// removePatronGroup
// Description: Reinitializes available and patrons allowing the table
// to be reused.
void Table::removePatronGroup(void){
	patrons = PatronGroup();
	available = true;
} // End removePatronGroup
