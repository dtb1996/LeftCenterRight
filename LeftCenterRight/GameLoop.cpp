#include "GameLoop.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void Game::WelcomePlayer()
{
	//Welcomes the player
	cout << "Welcome to Left Center Right" << endl;
	cout << "Created by Dillon Bellefeuille" << endl << endl;
}

void Game::GivePlayerOptions() const
{
	cout << "What would you like to do? (Enter a corresponding number)" << endl << endl;
	cout << "1: Read Rules" << endl << endl; //Allows the user to read through the rules
	cout << "2: Start Game" << endl << endl; //Allows the user to start the game
	cout << "3: Quit" << endl << endl; //Exits the game
}

void Game::GetPlayerInput(string& playerInput) const
{
	cin >> playerInput;
}

PlayerOptions Game::EvaluateInput(string& playerInput) const
{
	PlayerOptions chosenOption = PlayerOptions::None;

	if (playerInput.compare("1") == 0) //Runs if the user selects option 1
	{
		cout << "You have chosen to read the game rules." << endl << endl;
		chosenOption = PlayerOptions::ReadRules;
	}
	else if (playerInput.compare("2") == 0) //Runs if the user selects option 2
	{
		cout << "You have chosen to start the game." << endl << endl;
		chosenOption = PlayerOptions::Start;
	}
	else if (playerInput.compare("3") == 0) //Runs if the user selects option 3
	{
		cout << "You have chosen to Quit!" << endl << endl;
		chosenOption = PlayerOptions::Quit;
	}
	else //Runs if the user makes an invalid selection
	{
		cout << "I do not recognise that option, try again!" << endl << endl;
	}

	return chosenOption;
}

void Game::ReadRules()
{
	//Creates a string variable to hold the current line read in from the file
	string line;

	//Creates the file object and specifies the file name
	ifstream file("LCR_Rules.txt");

	//Executes if the file was successfully opened
	if (file.is_open())
	{
		//Reads the file line by line
		while (getline(file, line))
		{
			//Outputs the current line to the console
			cout << line << '\n';
		}

		//Closes the file
		file.close();
		cout << endl;
	}

	//Displays an error message if unable to open the file
	else cout << "Unable to open file";
}

void Game::PlayGame()
{
	//Sets shouldContinue to default value
	shouldContinue = true;

	//Runs  the setNumPlayers() method
	setNumPlayers();

	//Sets up a player object for each player
	Player *players = new Player[numPlayers];

	//Declares and initializes variables to be used for the game
	int i = 0;
	int j = 0;
	int k = 0;
	int numChips = 0;
	int playersWithChips = 0;
	string currentName = "";

	//Sets up each player object
	for (i = 0; i < numPlayers; i++)
	{
		//Prompts the user for the current player's name and sets it for that object
		cout << "Please enter the name of player " << (i + 1) << ": ";
		cin >> currentName; //Assigns the input to currentName
		players[i].SetName(currentName); //Sends currentName to the player's setName method
		players[i].setChips(3); //Set the player's chips to 3
	}

	RoleDice();

	cout << endl;
	
	do
	{
		//For loop that runs each round based on the number of players
		for (i = 0; i < numPlayers; i++)
		{
			//Assigns 0 to playersWithChips
			playersWithChips = 0;

			//Displays the player's name whose turn it is
			cout << "Your turn " << players[i].GetName() << endl << endl;

			//Checks to see if the current player has chips
			if (players[i].getChips() > 0)
			{
				//Resets the dice values
				players[i].setDice(0, 0, 0);

				//Resets the values in diceArray to 0
				for (j = 0; j < 3; j++)
				{
					diceArray[j] = 0;
				}

				//For loop that roles a die for each chip the player has up to three
				for (j = 0; j < (players[i].getChips()); j++)
				{
					//Calls RoleDice() and assigns the returned value to the current index in diceArray[]
					diceArray[j] = RoleDice();
				}
				//Sets the players dice values to match what was rolled
				players[i].setDice(diceArray[0], diceArray[1], diceArray[2]);

				//Loops through diceArray and takes action based on what was rolled
				for (k = 0; k < 3; k++)
				{
					//Switch statement that indicates what the player rolled and what happens to their chips
					switch (players[i].getDice(k))
					{
					case 1: players[i].adjustChips(-1); //Executes if a 1 was rolled (L)
						cout << "L - Pass one chip to the player on your left" << endl;
						//Passes a chip to the left based on the player's position
						if (i > 0)
						{
							players[i - 1].adjustChips(1);
						}
						else
						{
							players[numPlayers - 1].adjustChips(1);
						}
						break;
					case 2: players[i].adjustChips(-1); //Executes if a 2 was rolled (R)
						cout << "R - Pass one chip to the player on your right" << endl;
						//Passes a chip to the right based on the player's position
						if (i < (numPlayers - 1))
						{
							players[i + 1].adjustChips(1);
						}
						else
						{
							players[0].adjustChips(1);
						}
						break;
					case 3: players[i].adjustChips(-1); //Executes if a 3 was rolled (C)
						cout << "C - Place one chip in the center pot" << endl;
						break;
					case 4: ; //Executes if a 4 was rolled (*)
						cout << "*" << endl;
						break;
					case 5: ; //Executes if a 5 was rolled (*)
						cout << "*" << endl;
						break;
					case 6: ; //Executes if a 6 was rolled (*)
						cout << "*" << endl;
						break;
					case 0: ; //Executes if that die was not rolled
						break;
					}
				}

				cout << endl;

				//Sets the player's chips to 0 if it goes negative
				if (players[i].getChips() < 0)
				{
					players[i].setChips(0);
				}

				//Displays how many chips the players have
				for (j = 0; j < numPlayers; j++)
				{
					//Formats the output based on number of chips
					if (players[j].getChips() > 1 || players[j].getChips() == 0) //0 or more than 1 chips
					{
						cout << players[j].GetName() << " has " << players[j].getChips() << " chips" << endl;
					}
					else if (players[j].getChips() == 1) //1 chip
					{
						cout << players[j].GetName() << " has " << players[j].getChips() << " chip" << endl;
					}
				}

				cout << endl;
			}
			//Informs the current player that they have no chips and must pass to the next player
			else
			{
				cout << "You have 0 chips - Pass to the next player" << endl << endl;
			}

			//Checks how many players have chips
			for (j = 0; j < numPlayers; j++)
			{
				//Increases playersWithChips if the current player has chips
				if (players[j].getChips() > 0)
				{
					playersWithChips++;
				}
			}
			
			//Breaks out of the loop if only one player has chips
			if (playersWithChips == 1)
			{
				break;
			}

			//Prompts the user to press a key to continue to the next player
			system("pause");

			cout << endl;
		}

	} while (checkForWinner(playersWithChips) == true); //Calls checkForWinner() to see if there is a winner

	//Loops through the player objects to determine which player won
	for (i = 0; i < numPlayers; i++)
	{
		//Breaks out of the loop if the current player object has chips
		if (players[i].getChips() > 0)
		{
			break;
		}
	}

	//Displays a message indicating the winner
	cout << "You win " << players[i].GetName() << "!" << endl << endl;
}

void Game::setNumPlayers()
{
	//Resets numPlayers to 0
	numPlayers = 0;

	//Loops until the user enters a valid number of players
	while (numPlayers < 3)
	{
		cout << "Please enter the number of players: ";
		cin >> numPlayers;
		cout << endl;
		//Displays a warning and prompts the user to enter again if the number of players is too low
		if (numPlayers < 3)
		{
			cout << "At least three players are needed. Try again." << endl << endl;
		}
	}
}

bool Game::checkForWinner(int playersWithChips)
{
	//If more than one player has chips true is assigned to shouldContinue
	if (playersWithChips > 1)
	{
		shouldContinue = true;
	}
	//If only one player has chips false is assigned to shouldContinue
	else
	{
		shouldContinue = false;
	}

	return shouldContinue;
}

int Game::RoleDice()
{
	//Initializes variables
	int i = 0;
	dieNum = 0;
	
	//Generates a random number between 1 and 6
	dieNum = rand() % 6 + 1;

	return dieNum;
}


void Game::RunGame()
{
	//Runs the WelcomePlayer() method
	WelcomePlayer();

	//Declares a boolean shouldEnd and sets it to false
	bool shouldEnd = false;

	//Loops until the user selects "Quit"
	while (shouldEnd == false)
	{
		//Runs GivePlayerOptions() method
		GivePlayerOptions();

		//Declares a string to store the player input
		string playerInput;

		//Sends playerInput to GetPlayerInput()
		GetPlayerInput(playerInput);

		switch (EvaluateInput(playerInput)) //Switch that runs statements based on the selected option
		{
		case PlayerOptions::Quit: shouldEnd = true; //Sets shouldEnd to true if the user selects "Quit"
			break;
		case PlayerOptions::Start:; //Starts the game if that option is selected
			PlayGame();
			break;
		case PlayerOptions::ReadRules: ReadRules(); //Displays the rules if that option is selected
			break;
		}
	}
}


