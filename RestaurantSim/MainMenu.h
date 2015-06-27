#ifndef H_MAINMENU
#define H_MAINMENU
#pragma once

// MainMenu
// Description: The main menu controls for the application
class MainMenu
{
public:
	// Constructor/Destructor
	MainMenu(void);
	~MainMenu(void);

	static void run(void); // runs the menu

private:
	static void createConfig(void); // Allows a user to create a configuration file
	static void verifyConfig(void); // Verifies a configuration file
	static void about(void); // Shows program information

}; // End MainMenu

#endif
