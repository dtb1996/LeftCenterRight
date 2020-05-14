#pragma once

#include "Player.h"
#include "PlayerOptions.h"
#include <string>

class Game
{
private:

	//Declares private variables
	Player player;
	int numPlayers = 0;
	int diceArray[3] = { 0, 0, 0 };
	int dieNum = 0;
	bool shouldContinue = true;
	
	//Declares private GameLoop methods
	void WelcomePlayer();
	void ReadRules();
	void PlayGame();
	void setNumPlayers();
	int RoleDice();
	bool checkForWinner(int chips);
	void GivePlayerOptions() const;
	void GetPlayerInput(std::string& playerInput) const;
	PlayerOptions EvaluateInput(std::string& playerInput) const;

public:

	//Declares the RunGame() method
	void RunGame();
};

