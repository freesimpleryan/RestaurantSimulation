#include "MainMenu.h"
#include "Restaurant.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

// Constructor/Deconstructor
MainMenu::MainMenu(void){}
MainMenu::~MainMenu(void){}
// End Constructor/Deconstructor



// run
// Description: Entry point for application.
void MainMenu::run(void){

	Restaurant restaurant = Restaurant(); // Create restaurant
	int menu = -1; // Holds menu selection

	do{ // Main menu selection loop
		// Print menu
		system("cls");
		cout << "Restaurant Simulation" << endl;
		cout << "---------------------" << endl;
		cout << "1. Create configuration file" << endl;
		cout << "2. Verify configuration file" << endl;
		cout << "3. Run simulation" << endl;
		cout << "4. About" << endl;
		cout << "0. Exit" << endl;
		cout << "Enter a number for your selection." << endl;

		// Get input
		if(cin >> menu){
			switch(menu){
			case 1: // Create config file
				createConfig();
				break;
			case 2: // Verify config file
				verifyConfig();
				break;
			case 3: // Run simulation
				restaurant.run();
				break;
			case 4: // Show about info
				about();
				break;
			case 0: // Exit
				cout << "Exiting..." << endl;
				break;
			default: // Invalid input
				cout << "Invalid selection. Please try again." << endl;
				break;
			}
		}
		else if(cin.fail()){ // Catch input errors
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Invalid selection. Please try again." << endl;
		}
		
		std::system("pause");
	}while(menu != 0); // Exit on 0
} // End run



// createConfig
// Description: Allows a user to create a configuration file from inside
// the application.
void MainMenu::createConfig(void){
	
	std::system("cls");
	string input; // Holds user input

	// Clear cin buffer
	cin.clear();
	cin.ignore(10000, '\n');

	// Prompt
	cout << "Creating a new configuration file will overwrite all data in the current restaurant.config file." << endl;
	cout << "Do you want to continue and create a new configuration file? (y/n)" << endl;
	cin >> input;

	if(input == "y" || input == "Y"){ // Create new config
		
		string input[13]; // Holds datat entered
		bool flag = false; // Flags true once data for selection is valid
		cout << endl;
		
		// Each value is prompted then asked for and stored in the appropriate section of
		// the input array.

		// Restaurant name
		cin.ignore(10000, '\n');
		cout << "Enter restaurant name." << endl;
		getline(cin, input[0]);

		// Type
		do{
			cout << "Enter restaurant type - GOURMET, DINER, CASUAL" << endl;
			cin >> input[1];
			if(input[1] == "GOURMET" || input[1] == "DINER" || input[1] == "CASUAL"){
				flag = true;
			}
			else{
				cout << "Invalid entry. - Use ALL CAPS" << endl;
			}
		} while(!flag);
		flag = false;

		// Total tables
		do{
			cout << "Total number of tables:" << endl;
			cin >> input[2];
			if(stoi(input[2]) > 0){
				flag = true;
			}
			else{
				cout << "Invalid entry. Must be greater than 0." << endl;
			}
		} while(!flag);
		flag = false;

		// Table size
		do{
			cout << "Enter size of a table." << endl;
			cin >> input[3];
			if(stoi(input[3]) > 0){
				flag = true;
			}
			else{
				cout << "Invalid entry. Must be greater than 0." << endl;
			}
		} while(!flag);
		flag = false;

		// Waiter Skill
		do{
			cout << "Enter waiter skill - NEW_HIRE, SEASONED, PROFESSIONAL" << endl;
			cin >> input[4];
			if(input[4] == "NEW_HIRE" || input[4] == "SEASONED" || input[4] == "PROFESSIONAL"){
				flag = true;
			}
			else{
				cout << "Invalid entry. Use CAPS." << endl;
			}
		} while(!flag);
		flag = false;

		// Start capacity
		do{
			cout << "Enter starting capacity - SLOW, BUSY, SLAMMED" << endl;
			cin >> input[5];
			if(input[5] == "SLOW" || input[5] == "BUSY" || input[5] == "SLAMMED"){
				flag = true;
			}
			else{
				cout << "Invalid entry. Use CAPS." << endl;
			}
		} while(!flag);
		flag = false;

		// Arrive interval
		do{
			cout << "Enter the time frequency for patron groups to arrive (in minutes)" << endl;
			cin >> input[6];
			if(stoi(input[6]) > 0){
				flag = true;
			}
			else{
				cout << "Invalid entry. Must be greater than 0." << endl;
			}
		} while(!flag);
		flag = false;

		// Min arrive
		do{
			cout << "Enter minimum patron groups to arrive per interval" << endl;
			cin >> input[7];
			if(stoi(input[7]) >= 0){
				flag = true;
			}
			else{
				cout << "Invalid entry. Must be 0 or greater." << endl;
			}
		} while(!flag);
		flag = false;

		// Max arrive
		do{
			cout << "Enter maximum patron groups to arrive" << endl;
			cin >> input[8];
			if(stoi(input[8]) > stoi(input[7])){
				flag = true;
			}
			else{
				cout << "Invalid entry. Must be greater then " << input[7] << endl;
			}
		} while(!flag);
		flag = false;

		// Min size
		do{
			cout << "Enter minimum number of patrons per group" << endl;
			cin >> input[9];
			if(stoi(input[9]) > 0){
				flag = true;
			}
			else{
				cout << "Invalid entry. Must be greater than 0." << endl;
			}
		} while(!flag);
		flag = false;

		// Max size
		do{
			cout << "Enter maximum number of patrons per group" << endl;
			cin >> input[10];
			if(stoi(input[10]) > stoi(input[9]) && stoi(input[10]) <= stoi(input[3])){
				flag = true;
			}
			else{
				cout << "Invalid entry. Must be greater then " << input[9] << " and no more than " << input[3] << endl;
			}
		} while(!flag);
		flag = false;

		// Update interval
		do{
			cout << "Enter the interval to display updates (in minutes)" << endl;
			cin >> input[11];
			if(stoi(input[11]) > 0){
				flag = true;
			}
			else{
				cout << "Invalid entry. Must be greater than 0." << endl;
			}
		} while(!flag);
		flag = false;

		// Time to run
		do{
			cout << "Enter the length of time for the simulation to run (in minutes)" << endl;
			cin >> input[12];
			if(stoi(input[12]) > 0){
				flag = true;
			}
			else{
				cout << "Invalid entry. Must be greater than 0." << endl;
			}
		} while(!flag);
		flag = false;

		// Write to config
		ofstream outFile;
		outFile.open("restaurant.config");
		outFile << "# Restaurant Info\n# Restaurant Name" << endl;
		outFile << "name = " << input[0] << endl;
		outFile << "# Restaurant Type - DINER, CASUAL, GOURMET" << endl;
		outFile << "type = " << input[1] << endl;
		outFile << "# Tables\n# Total number of tables" << endl;
		outFile << "totalTables = " << input[2] << endl;
		outFile << "# Size of a table" << endl;
		outFile << "tableSize = " << input[3] << endl;
		outFile << "# Waiter skill level - NEW_HIRE, SEASONED, PROFESSIONAL" << endl;
		outFile << "waiterSkill = " << input[4] << endl;
		outFile << "# Start Capacity - SLOW, BUSY, SLAMMED" << endl;
		outFile << "startCapacity = " << input[5] << endl;
		outFile << "# Patron Group Options\n# Interval for Patron Groups to arrive" << endl;
		outFile << "arriveInterval = " << input[6] << endl;
		outFile << "# Min and max for Patron Groups to arrive" << endl;
		outFile << "minArrive = " << input[7] << endl;
		outFile << "maxArrive = " << input[8] << endl;
		outFile << "# Min and max size of Patron Groups" << endl;
		outFile << "minSize = " << input[9] << endl;
		outFile << "maxSize = " << input[10] << endl;
		outFile << "# Display Info\n# Minute interval to display updates" << endl;
		outFile << "update = " << input[11] << endl;
		outFile << "# Length of time in minutes for simulation to run" << endl;
		outFile << "timeToRun = " << input[12];
		outFile.close();

	}
	else{ // User does not want to overwrite or create config
		cout << "Restaurant.config has not been altered." << endl;
	}
	

} // End createConfig



// verifyConfig
// Description: Verifies an existing configuration and
// shows the values.
void MainMenu::verifyConfig(void){

	std::system("cls");

	ifstream config; // Reads config file
	

	string id, eq, val, temp; // Reads id, equal sign, value, and temp value for as needed
	int counter = 0; // Holds number of reads for config file
	int MAX = 13; // Number of configurable values

	config.open("restaurant.config");
	// Read config file
	if(config.is_open()){

		while(!config.eof()){ // Read loop
			config >> id; // Get first word
			if(id[0] == '#'){ // Ignore comment lines with # at beginning
				config.ignore(10000, '\n');
				continue;
			}
			config >> eq >> val; // Get and test for equal sign and get value

			// As long as eq is "=", the line will be tested for values.
			// Format: variable = value
			if(eq == "="){

				if(id == "name"){ // Validate name
					counter++;
					while(config.peek() != '\n'){
						val += config.get();
					}
					if(val != "")
						cout << "Restaurant Name: " << val << " --OK" << endl;
				}

				else if(id == "type"){ // Validate type
					counter++;
					if(val == "GOURMET" || val == "DINER" || val == "CASUAL")
						cout << "Restaurant Type: " << val << " -- OK" << endl;
					else
						cout << "Restaurant Type: " << val << " -- FAIL" << endl;
				}

				else if(id == "totalTables"){ // Validate total tables
					counter++;
					if(stoi(val) > 0)
						cout << "Total Tables: " << val << " -- OK" << endl;
					else
						cout << "Total Tables: " << val << " -- FAIL" << endl;
				}

				else if(id == "tableSize"){ // Validate Table Size
					counter++;
					if(stoi(val) > 0)
						cout << "Table Size: " << val << " -- OK" << endl;
					else
						cout << "Table Size: " << val << " -- FAIL" << endl;
				}

				else if(id == "waiterSkill"){ // Validate Waiter Skill level
					counter++;
					if(val == "NEW_HIRE" || val == "SEASONED" || val == "PROFESSIONAL")
						cout << "Waiter Skill: " << val << " -- OK" << endl;
					else
						cout << "Waiter Skill: " << val << " -- FAIL" << endl;
				}

				else if(id == "startCapacity"){ // Validate start capacity value
					counter++;
					if(val == "SLOW" || val == "BUSY" || val == "SLAMMED")
						cout << "Start Capacity: " << val << " -- OK" << endl;
					else
						cout << "Waiter Skill: " << val << " -- FAIL" << endl;
				}

				else if(id == "arriveInterval"){ // Validate arrive interval
					counter++;
					if(stoi(val) > 0)
						cout << "Patron Group Arrive Interval: " << val << " -- OK" << endl;
					else
						cout << "Patron Group Arrive Interval: " << val << " -- FAIL" << endl;
				}

				else if(id == "minArrive"){ // Validate minimum arrive number
					counter++;
					if(stoi(val) >= 0)
						cout << "Minimum Patron Group Arrive: " << val << " -- OK" << endl;
					else
						cout << "Minimum Patron Group Arrive: " << val << " -- FAIL" << endl;
				}

				else if(id == "maxArrive"){ // Validate max arrive - NOTE: Only checks that the value is a real number
					counter++;
					if(stoi(val) > 0)
						cout << "Maximum Patron Group Arrive: " << val << " -- OK" << endl;
					else
						cout << "Maximum Patron Group Arrive: " << val << " -- FAIL" << endl;
				}

				else if(id == "minSize"){ // Validate minimum group size
					counter++;
					if(stoi(val) > 0)
						cout << "Minimum Patron Group Size: " << val << " -- OK" << endl;
					else
						cout << "Minimum Patron Group Size: " << val << " -- FAIL" << endl;
				}

				else if(id == "maxSize"){ // Validate maximum group size - NOTE: Only validates that the number is a real number
					counter++;
					if(stoi(val) > 0)
						cout << "Maximum Patron Group Size: " << val << " -- OK" << endl;
					else
						cout << "Maximum Patron Group Size: " << val << " -- FAIL" << endl;
				}

				else if(id == "update"){ // Validate update interval
					counter++;
					if(stoi(val) > 0)
						cout << "Update Interval (minutes): " << val << " -- OK" << endl;
					else
						cout << "Update Interval (minutes): " << val << " -- FAIL" << endl;
				}

				else if(id == "timeToRun"){ // Validate time to run
					counter++;
					if(stoi(val) > 0)
						cout << "Time to Run (minutes): " << val << " -- OK" << endl;
					else
						cout << "Time to Run (minutes): " << val << " -- FAIL" << endl;
				}

			} // End if for reading values

		} // End while

		config.close();

		// Data results
		cout << endl << counter << " of " << MAX << " configurations found." << endl << endl;
		cout << "Review the contents of 'restaurant.conifg or create a new file" << endl;
		cout << "if there are any discrepencies. Otherwise default values will be used." << endl;

	}
	else{ // No config found
		cout << "Restaurant.config not found. Default simulation values will be used." << endl;
	}

} // End validateConfig



// about
// Description: Displays program information
void MainMenu::about(void){
	cout << "Restaurant Simulator" << endl;
	cout << "Written by Ryan Brown" << endl << endl;
	cout << "Description: This program simulates groups of patrons" << endl;
	cout << "waiting, dining, and leaving a restaurant based on" << endl;
	cout << "configurable parameters." << endl << endl;
} // End abou
