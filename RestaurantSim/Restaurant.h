#ifndef H_RESTAURANT
#define H_RESTAURANT
#pragma once

#include <string>
#include <list>
#include <vector>
#include "Table.h"
#include "PatronGroup.h"

using namespace std;

// Restaurant
// Description: Main class for simulation program
class Restaurant
{
public:
	// Constructors
	Restaurant(void);
	~Restaurant(void);

	void run(void); // Runs the simulation

private:
	// Setup variables
	string name; // Restaurant name
	string type; // Type - DINER, CASUAL, GOURMET

	int totalTables; // Total tables in restaurant
	int tableSize; // Number of seats at a table
	string waiterSkill; // NEW_HIRE, SEASONED, VETERAN
	
	string startCapacity; // How full the restaurant is at the start of the simulation - SLOW, BUSY, SLAMMED
	int updateInterval; // How often to display the restaurant information to the console
	int totalTimeToRun; // How long in minutes to run the simulation
	int timeRun; // How long the simulation has ran

	// Patron Group variables
	int patronGroupMinSize; // Minimum size of a patron group
	int patronGroupMaxSize; // Maximum size of a patron group
	int patronGroupArriveInterval; // Interval for patron groups to arrive
	int patronGroupMinArrive; // Minimum patron groups to arrive per interval
	int patronGroupMaxArrive; // Maximum patron groups to arrive per interval
	

	// Line and tables
	list<PatronGroup> line; // PatronGroups waiting to be seated
	vector<Table> tables; // Tables in the restaurant

	// Logging
	int averageWaitTime; // Average wait time per PatronGroup
	int averageTotalTime; // Average total time spent at the restaurant per PatronGroup
	int averageInLine; // Average number of patrongroups in line
	int totalPatronGroups; // Total PatronGroups that have entered the restaurant

	// Setup
	void setValues(void); // Initialize values to defaults or read from file
	void setupRestaurant(string); // Start restaurant with the given startCapacity

	// Running
	void seatLine(void); // Attempt to seat PatronGroups in line
	void showData(void); // Show data to console
	void advanceTime(void); // Advance time for all groups and total time for simulation
	void busTables(void); // Remove PatronGroups if they are finished

	// I/O
	void readConfig(void); // Read restaurant.config and set values
	void writeToOutput(void); // Write the data for the run of the simulation
}; // End Restaurant

#endif
