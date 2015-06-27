#include "Restaurant.h"
#include "Waiter.h"
#include "PatronFactory.h"
#include "TimeStamp.h"
#include <iostream>
#include <fstream>
#include <iterator>
#include <exception>

// Default Constructor/Deconstructor
Restaurant::Restaurant(void){}
Restaurant::~Restaurant(void){}
// End Default Constructor/Deconstructor



// run
// Description: Runs the simulation
void Restaurant::run(void){
	TimeStamp::set(); // Setup timestamp for data writing

	setValues(); // Initialize default values and attempt to read config file

	int groups = 0;

	// Main loop
	while(timeRun <= totalTimeToRun){
		
		if(timeRun > 0 && timeRun % patronGroupArriveInterval == 0){ // If patron groups should arrive at the time interval

			(patronGroupMinArrive == 0) ? // Account for a 0 as the minimum
				groups = rand() % patronGroupMaxArrive :
				groups = rand() % patronGroupMinArrive + patronGroupMaxArrive;

			totalPatronGroups += groups;

			for(int i = 0; i < groups; i++){ // Add number of groups to arrive to line
				line.push_back(PatronFactory::newPatronGroup());
			}
		} // End generating new PatronGroups

		busTables(); // Remove finished PatronGroups
		seatLine(); // Seat PatronGroups from the line if possible

		if(timeRun > 0 && timeRun % updateInterval == 0){ // Check if data should be shown for the current time interval
			showData();
		}

		advanceTime(); // Advance time for all PatronGroups

	} // End main loop

	writeToOutput(); // Write data to output file

} // End run



// setValues
// Description: Initializes the default values and then attempts
// to read the restaurant.confg file.
void Restaurant::setValues(void){

	// Initialize values
	timeRun = 0;
	line = list<PatronGroup>();
	tables = vector<Table>();
	totalPatronGroups = 0;
	averageTotalTime = 0;
	averageWaitTime = 0;
	averageInLine = 0;

	// Set defaults
	name = "Restaurant";
	type = "DINER";

	totalTables = 20;
	tableSize = 4;

	waiterSkill = "SEASONED";

	startCapacity = "SLOW";

	patronGroupArriveInterval = 30;
	patronGroupMinArrive = 0;
	patronGroupMaxArrive = 3;
	patronGroupMinSize = 1;
	patronGroupMaxSize = tableSize;

	updateInterval = 15;

	totalTimeToRun = 600;

	readConfig(); // Attempt to read config and overwrite defaults

	Waiter::setSkillLevel(waiterSkill); // Set waiter skill level

	// Create tables at correct quantity and size
	tables.resize(totalTables);
	for(int i = 0; i < totalTables; i++){
		tables[i] = Table(tableSize);
	}

	// Setup PatronFactory
	PatronFactory::setDefaultMinMax(patronGroupMinSize, patronGroupMaxSize);
	PatronFactory::setRestaurantType(type);

	// Write header to logfile
	string filePath = "log" + TimeStamp::get() + ".csv";
	ofstream output;

	output.open(filePath, ofstream::app);
	output << "ID;Number Patrons;Total Time;Wait Time;Dining Time;Target Dining Time; Waiter Time;\n";
	output.close();

	setupRestaurant(startCapacity);
	seatLine();
} // End setValues



// readConfig
// Description: Attempts to read restaurant.config and loads any
// found values. See MainMenu::verifyConfig for more information.
void Restaurant::readConfig(void){
	ifstream config;
	config.open("restaurant.config");

	string id, eq, val; // Same as MainMenu::verifyConfig

	if(config.is_open()){ // Check if exists and is open
		// Read loop
		while(!config.eof()){

			config >> id;
			if(id[0] == '#'){ // Ignore comments
				config.ignore(10000, '\n');
				continue;
			}

			config >> eq >> val;
			// If valid pattern...
			if(eq == "="){
				if(id == "name"){
					while(config.peek() != '\n'){
						val += config.get();
					}
					name = val;
				}
				else if(id == "type")
					type = val;
				else if(id == "totalTables" && stoi(val) > 0)
					totalTables = stoi(val);
				else if(id == "tableSize" && stoi(val) > 0)
					tableSize = stoi(val);
				else if(id == "waiterSkill")
					waiterSkill = val;
				else if(id == "startCapacity")
					startCapacity = val;
				else if(id == "arriveInterval" && stoi(val) > 0)
					patronGroupArriveInterval = stoi(val);
				else if(id == "minArrive" && stoi(val) >= 0)
					patronGroupMinArrive = stoi(val);
				else if(id == "maxArrive" && stoi(val) > patronGroupMinArrive)
					patronGroupMaxArrive = stoi(val);
				else if(id == "minSize" && stoi(val) > 0)
					patronGroupMinSize = stoi(val);
				else if(id == "maxSize" && stoi(val) <= tableSize)
					patronGroupMaxSize = stoi(val);
				else if(id == "update" && stoi(val) > 0)
					updateInterval = stoi(val);
				else if(id == "timeToRun" && stoi(val) > 0)
					totalTimeToRun = stoi(val);
			} // End value set
		} // End read loop

		config.close();
		cout << "Config file loaded." << endl;
	}
	else{ // No config file found
		cout << "Config file not found. Default values will be used." << endl;
	}

	std::system("pause");
	std::system("cls");
} // End readConfig



// seatLine
// Description: Attempts to seat any PatronGroups in line
void Restaurant::seatLine(void){

	PatronGroup temp;

	if(time > 0)
		averageInLine += line.size(); // Accumulate for average

	if(line.size() > 0){ // Only run if PatronGroups are in line

		// Check each table to see if it is available or not
		for(int i = 0; i < totalTables; i++){

			if(tables[i].isAvailable() && line.size() > 0){ // If the table is available, seat PatronGroup at front of line
				temp = line.front();
				line.pop_front();
				tables[i].seatPatronGroup(temp);
			}

		} // End for
	}

} // End seatLine



// busTables
// Description: Removes a PatronGroup from a table and replaces it with the default constructor.
// This signals a table is available.
void Restaurant::busTables(void){

	// Check each table
	for(int i = 0; i < tables.size(); i++){
		// If the table is finished and is NOT the default id of 0, log their times and remove the group
		if(tables[i].getPatronGroup().isFinished() && tables[i].getPatronGroup().getId() != 0){
			averageWaitTime += tables[i].getPatronGroup().getTotalWaitTime();
			averageTotalTime += tables[i].getPatronGroup().getTotalTime();
			tables[i].removePatronGroup();
		}
	} // End for
} // End busTables



// advanceTime
// Description: Advances time for each PatronGroup in line or at a table as well as the total time
// for the simulation.
void Restaurant::advanceTime(void){

	// Advance time for PatronGroups in line
	if(line.size() > 0){
		for(list<PatronGroup>::iterator iterator = line.begin(), end = line.end(); iterator != end; ++iterator){
			iterator->advanceWaitTime();
		}
	}

	// Advance time for Tables
	for(int i = 0; i < tables.size(); i++){
		if(!tables[i].isAvailable()){
			tables[i].getPatronGroup().advanceDiningTime();
		}
	}

	timeRun++; // Advance simulation time

} // End advanceTime




// showData
// Description: Prints the current simulation data to the screen.
void Restaurant::showData(void){
	
	// Get current tables in use
	int tablesInUse = 0;
	for(int i = 0; i < tables.size(); i++){
		if(!tables[i].isAvailable())
			tablesInUse++;
	}

	// Print data
	cout << endl;
	cout << "Restaurant Name: " << name << endl;
	cout << "Total tables: " << totalTables << endl;
	cout << "Restaurant Type: " << type << endl;
	cout << "Total time passed: " << timeRun << endl;
	cout << "Total time to run: " << totalTimeToRun << endl;
	cout << "Waiter skill level: " << waiterSkill << endl;
	cout << "Total tables in use: " << tablesInUse << endl;
	cout << "PatronGroups in line: " << line.size() << endl;
	cout << "Total PatronGroups for the day: " << totalPatronGroups << endl;
	cout << "Average wait time: " << averageWaitTime / totalPatronGroups << endl;
	cout << "Average total visit time: " << averageTotalTime / totalPatronGroups << endl;
	system("pause");
} // End showData



// setupRestaurant
// Description: Initializes the restaurant to its level of business at the start of the simulation
// per the program specifications.
void Restaurant::setupRestaurant(string startCapacity){

	int toSeat; // Number of PatronGroups to generate
	int minAt; // Minimum capacity
	int min; // Minimum Patrons in each PatronGroup
	int counter = 0; // Tracks total number of patrons
	
	transform(startCapacity.begin(), startCapacity.end(), startCapacity.begin(), toupper); // Validation

	// Per program specifications
	if(startCapacity == "SLOW"){
		toSeat = totalTables / 2;
		minAt = toSeat * 0.75;
		min = 2;

		PatronFactory::setMinMax(1, min);

	}
	else if(startCapacity == "BUSY"){
		toSeat = totalTables / 2;
		minAt = toSeat * 0.75;
		min = 2;

		PatronFactory::setMin(1);
	}
	else if(startCapacity == "SLAMMED"){
		toSeat = totalTables;
		minAt = toSeat * 0.75;
		min = 3;

		PatronFactory::setMin(3);	
	}
	else{ // Invalid entry - do nothing
		return;
	}

	// Create minAt number of PatronGroups with given min as PatronGroup minimum guests
	while(counter <= minAt){
		line.push_back(PatronFactory::newPatronGroup());
		counter++;
	}

	PatronFactory::resetMinMax();

	// Generate remaining PatronGroups with full range of guests
	while(counter <= toSeat){
		line.push_back(PatronFactory::newPatronGroup());
		counter++;
	}

	totalPatronGroups += counter; // Add all generated PatronGroups to the restaurant total

} // End setupRestaurant



// writeToOutput
// Description: Writes the statistics.dat file.
void Restaurant::writeToOutput(void){
	
	string file = "statistics" + TimeStamp::get() + ".dat";
	ofstream output(file);
	if(output.is_open()){
		output << "Restaurant Name: " << name << endl;
		output << "Restaurant Type: " << type << endl;
		output << "Total time to run: " << totalTimeToRun << endl << endl;

		output << "Total tables: " << totalTables << endl;
		output << "Table size: " << tableSize << endl;
		output << "Waiter skill level: " << waiterSkill << endl << endl;

		output << "Patron group arrive inteval: " << patronGroupArriveInterval << endl;
		output << "Minimum PatronGroup size: " << patronGroupMinSize << endl;
		output << "Maximum PatronGroup size: " << patronGroupMaxSize << endl;
		output << "Minimum PatronGroups to arrive: " << patronGroupMinArrive << endl;
		output << "Maximum PatronGroups to arrive: " << patronGroupMaxArrive << endl << endl;

		output << "Total PatronGroups for the day: " << totalPatronGroups << endl;
		output << "Average PatronGroups in line: " << averageInLine / totalTimeToRun << endl;
		output << "Average wait time: " << averageWaitTime / totalPatronGroups << endl;
		output << "Average total visit time: " << averageTotalTime / totalPatronGroups;

	output.close();

	} // End write
} // End writeToOutput
