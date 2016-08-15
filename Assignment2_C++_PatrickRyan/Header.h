#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
/*
Author: Patrick Ross - Ryan Jameson
Date: July 29, 2016.
Assignment #2
Professor: Matt Wilson
*/

using namespace std;

vector<string> userVector;

//Declare Classes
//High Score Manager class
class HighScoreManager {

	struct {
		string Username;
		string Score;
		string Time;
	};
public:
	//creates highscore
	void CreateHighScore(string username, string score, string time) {
		//saving info to struct
		Username = username;
		Score = score;
		Time = time;
		//updates the highscore list
		UpdateHighScore();
	}//CreateHighScore

	//updates users highscore
	void UpdateHighScore() {
		//variables
		fstream scoreFile;
		vector<string> scoreVector;

		//adds HighScores.text to scoreVector
		scoreFile.open("..\\HighScores.txt");
		if (scoreFile)
		{
			//read the lines from the HighScore file, insert it into the vector.
			for (string line; getline(scoreFile, line);)
			{
				scoreVector.push_back(line);
			}
			// Close the file.
			scoreFile.close();

			int maxIndex = scoreVector.size();
			for (int index = 1; index < maxIndex;) {
				if (stoi(Score) < stoi(scoreVector.at(maxIndex - 1))) {
					scoreVector.push_back(Username);
					scoreVector.push_back(Score);
					scoreVector.push_back(Time);
					break;

				}
				if (stoi(Score) > stoi(scoreVector.at(maxIndex - 1)) && stoi(Score) < stoi(scoreVector.at(maxIndex - 4))) {
					scoreVector.insert(scoreVector.begin() + maxIndex - 2, Username);
					scoreVector.insert(scoreVector.begin() + maxIndex -1, Score);
					scoreVector.insert(scoreVector.begin() + maxIndex, Time);
					cout << "lies \n";
					break;

				}
				if (stoi(Score) > stoi(scoreVector.at(index))) {
					scoreVector.insert(scoreVector.begin() + index - 1, Username);
					scoreVector.insert(scoreVector.begin() + index, Score);
					scoreVector.insert(scoreVector.begin() + index + 1, Time);
					break;
				}
				index = index + 3;
			}
			scoreFile.open("..\\HighScores.txt");
			if (scoreFile)
			{
				//write first 30 elements of scoreVector to the file
				int maxIndex = scoreVector.size();
				if (scoreVector.size() > 30) {
					maxIndex = 30;
				}
				for (int index = 0; index < maxIndex; index++) {
					scoreFile << scoreVector.at(index) << "\n";
				}
				//close HighScores.txt
				scoreFile.close();
			}//end of if file opens
			else {
				// Display an error message.
				cout << "Error adding new score.\n";
				system("PAUSE");
				exit(1);
			}//end of else
			system("PAUSE");
		}
		else {
			// Display an error message.
			cout << "Error opening the file.\n";
			system("PAUSE");
			exit(1);
		}
	}//end of UpdateHighScore
	//prints highscore
	void PrintHighScore() {

		//variables
		fstream scoreFile;
		vector<string> scoreVector;

		//adds HighScores.text to scoreVector
		scoreFile.open("..\\HighScores.txt");
		if (scoreFile)
		{
			//read the lines from the HighScore file, insert it into the vector.
			for (string line; getline(scoreFile, line);)
			{
				scoreVector.push_back(line);
			}
			// Close the file.
			scoreFile.close();
		}
		else {
			// Display an error message.
			cout << "Error opening the file.\n";
			system("PAUSE");
			exit(1);
		}
		cout << "\n\n" <<
			setw(15) << "Place:" <<
			setw(15) << "Username:" <<
			setw(15) << "Score:" <<
			setw(15) << "Time:" << '\n';
		int place = 1;
		for (int index = 0; index < scoreVector.size() - 2; index = index + 3)
		{
			cout <<
				setw(15) << place << "." <<
				setw(15) << scoreVector.at(index) <<
				setw(15) << scoreVector.at(index + 1) <<
				setw(15) << scoreVector.at(index + 2) << '\n';
			place++;
		}
	}//end of PrintHighScore

};//end of highscoremanager

//User Manager Class
class User {
	struct {
		string Username;
		string Name;
		string Email;
		string Password;
	};
public:

	//getters for struct
	string getUsername() {
		return Username;
	}
	string getFirstName() {
		return Name;
	}
	string getEmail() {
		return Email;
	}
	string getPassword() {
		return Password;
	}

	//logs user in
	void Login(string username, string name, string email, int index) {
		//Declaration of variable
		bool auth = false;
		string input;
		do {
			cout << "Please enter your password " << name << ". Enter 1 to exit the application. \n";
			getline(cin, input);
			if (input == userVector.at(index + 3)) {
				auth = true;
			}
			if (input == "1") {
				cout << "Exiting application, ";
				system("PAUSE");
				exit(1);
			}
		} while (!auth);
		Username = username;
		Name = name;
		Email = email;
		Password = input;
		cout << "You have logged in successfully" << "\n";
	}//end of Login

	//checks if user exists
	void CheckIfUserExist() {

		//variables to be used throughout the function
		string username;
		string name;
		string email;
		string password;
		char match = 0;

		//gets users name
		cout << "Welcome, please enter your username. \nA new account will be created if the username entered does not exist. \n";
		getline(cin, username);
		//convert string to lowercase
		transform(username.begin(), username.end(), username.begin(), ::tolower);
		int maxIndex = userVector.size();
		for (int index = 0; index < maxIndex;)
		{
			//if string compare is a match send user info to login
			if (username == userVector.at(index)) {
				name = userVector.at(index + 1);
				email = userVector.at(index + 2);
				cout << "Welcome Back " << name << "!" << "\n";
				Login(username, name, email, index);//logs user in
				match = 1;
				system("PAUSE");
				break;
			}
			index = index + 4;
		}
		//if the name entered has never logged in, create user and give greeting
		if (match == 0) {
			cout << "Welcome Newbie, please enter your first name. \n";
			getline(cin, name);
			cout << "Please enter your email. \n";
			getline(cin, email);
			cout << "Please enter your account password. \n";
			getline(cin, password);
			UpdateUserList(true, username, name, email, password);//adds new user to db
			cout << "Your account has been created " << "successfully " << name << "! \n";
			Login(username, name, email, maxIndex);//logs user in
			system("PAUSE");
		}
	}//end of CheckIfUserExist

	//adds new user / updates exsiting user
	void UpdateUserList(bool newOrUpdate, string username, string name, string email, string password) {
		//add new user
		if (newOrUpdate) {
			userVector.push_back(username);
			userVector.push_back(name);
			userVector.push_back(email);
			userVector.push_back(password);
		}
		//change existing user info
		else {
			//declaring variables
			bool quit = false;
			int option;
			string input;
			while (!quit) {
				do {
					cout << "Update User Menu \n";
					cout << "1. Change Name. \n";
					cout << "2. Change Email. \n";
					cout << "3. Change Password. \n";
					cout << "4. Delete User Account. \n";
					cout << "5. Save Changes. \n\n";
					cin >> option;
				} while (option < 1 || option > 5);
				switch (option) {

					//change name
				case 1:
					cout << "Enter new name. \n";
					cin >> name;
					break;

					//change email
				case 2:
					cout << "Enter new email. \n";
					cin >> email;
					break;

					//change password
				case 3:
					cout << "Enter new password. \n";
					cin >> password;
					break;

					//delete account
				case 4:
					DeleteUser(username);
					break;

					//saves changes, returns to main.
				case 5:
					int maxIndex = userVector.size();
					for (int index = 0; index < maxIndex;)
					{
						//if string compare is a match, grab index
						if (username == userVector.at(index)) {
							//save changes to current user
							Username = username;
							Name = username;
							Email = email;
							Password = password;
							//save changes to userVector
							userVector.at(index + 1) = name;
							userVector.at(index + 2) = email;
							userVector.at(index + 3) = password;
							break;
						}//end of if
						index = index + 4;
					}//end of for loop
					quit = true;
					break;
				}//end of switch
			}//end of while
		}//end of else
		//open names.txt to write to the file
		fstream userFile;
		userFile.open("..\\Users.txt");
		//if opened
		if (userFile) {
			//write userVector to file
			int maxIndex = userVector.size();
			for (int index = 0; index < maxIndex; ++index) {
				userFile << userVector.at(index) << "\n";
			}
			cout << "Records saved successfully\n";
			//close Users.txt
			userFile.close();
		}//end of if file opens
		else {
			// Display an error message.
			cout << "Error saving user information.\n";
			system("PAUSE");
			exit(1);
		}//end of else
	}//end of UpdateUserList

	//deletes user
	void DeleteUser(string username) {
		//confirmation message before deleting user account
		string input;
		cout << "Are you sure you want to delete " << username << "? Enter \"yes\" to confirm. This is irreversable\n";
		cin >> input;
		if (input == "yes")
		{
			int maxIndex = userVector.size();
			for (int index = 0; index < maxIndex;)
			{
				//if string compare is a match, grab index
				if (username == userVector.at(index)) {
					//save changes to userVector
					userVector.erase(userVector.begin() + index, userVector.begin() + index + 4);
					break;
				}//end of if
				index = index + 4;
			}//end of for loop

			//saves changes to database
			fstream userFile;
			remove("..\\Users.txt");
			ofstream newFile("..\\Users.txt");
			userFile.open("..\\Users.txt");
			//if opened
			if (userFile) {
				//userFile.clear();
				//write userVector to file
				int maxIndex = userVector.size();
				for (int index = 0; index < maxIndex; ++index) {
					userFile << userVector.at(index) << "\n";
				}
				//close Users.txt
				userFile.close();
			}//end of if file opens
			else {
				// Display an error message.
				cout << "Error deleting user.\n";
				system("PAUSE");
				exit(1);
			}//end of else
			cout << "User " << username << " deleted successfully. \n";
			system("PAUSE");
			exit(1);
		}
		else {
			cout << "Cancelling account deletion. \n";
			system("PAUSE");
		}
	}//end of DeleteUser

	//sets users highscore
	void SetHighScore(string username) {
		//declaring variables
		string input;
		string score;
		string time;
		bool next = false;

		do {
			cout << "Please enter your new score, whole numbers only. \n";
			cin >> input;
			if (all_of(input.begin(), input.end(), isdigit)) {
				score = input;
				next = true;
			}
		} while (!next);
		next = false;
		do {
			cout << "Please enter your time in seconds. \n";
			cin >> input;
			if (all_of(input.begin(), input.end(), isdigit)) {
				time = input;
				next = true;
			}
		} while (!next);
		HighScoreManager ScoreManager;
		ScoreManager.CreateHighScore(username, score, time);
	}//end of SetHighScore
};//end of user


//Declare prototypes
void PrintMenu();