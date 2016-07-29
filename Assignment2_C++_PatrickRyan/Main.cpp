#include <stdlib.h>
#include "Header.h"
/*
Author: Patrick Ross - Ryan Jameson
Date: July 29, 2016.
Assignment #2
Professor: Matt Wilson
*/

//global variables

//prototypes


int main() {
	
	//Declaration of variables
	int choice;
	bool quit = false;
	User User;
	HighScoreManager ScoreManager;
	fstream userFile;

	//adds Users.text to userVector
	userFile.open("..\\Users.txt");
	if (userFile)
	{
		//read the lines from the name file, insert it into two vectors.
		for (string line; getline(userFile, line);)
		{
			userVector.push_back(line);
		}
		// Close the file.
		userFile.close();
	}
	else {
		// Display an error message.
		cout << "Error opening the file.\n";
		system("PAUSE");
		exit(1);
	}

	//if an old user, log in, if new, create new account and log in.
	User.CheckIfUserExist();

	while (!quit) {
		do {
			//prints navigation menu
			PrintMenu();
			cin >> choice;
		} while (choice < 1 || choice > 5);

		//This switch controls where user is navigated to on printed menu
		switch (choice) {

			//This case allows the user to update account information
		case 1:
			User.UpdateUserList(false, User.getUsername(), User.getFirstName(), User.getEmail(), User.getPassword());
			break;

			//This case sets a new highscore
		case 2:
			User.SetHighScore();
			break;

			//This case deletes the current user account
		case 3:
			User.DeleteUser(User.getUsername());
			break;

			//This case displays all high score
		case 4:
			ScoreManager.PrintHighScore();
			break;

			//This case exits the application
		case 5:
			quit = true;
			cout << "Exiting application, ";
			break;
		}//end of switch
	}//end of while
	system("PAUSE");
	return 0;

}//end of main

void PrintMenu() {
	cout << "Main Menu \n";
	cout << "1. Update User Info. \n";
	cout << "2. Set High Score \n";
	cout << "3. Delete User Account \n";
	cout << "4. Display All High Scores\n";
	cout << "5. Exit Application \n";
	cout << "\nPlease select a number: \n\n			";
}//end of PrintMenu function