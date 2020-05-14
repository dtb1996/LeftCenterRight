#pragma once

#include <string>

class Player
{
private:
	//Declares variables to be used for each player object
	std::string name;
	std::string playerName = "";
	int diceArray[3] = { 0, 0, 0 };
	int numChips = 0;

public:
	Player()
	{
	}

	//Sets the player's name as the inputted string
	void SetName(const std::string& name)
	{
		playerName = name;
	}

	//Returns the player's name
	const std::string& GetName() const
	{
		return playerName;
	}

	//Sets the number of chips to the inputted integer
	void setChips(int chips)
	{
		numChips = chips;
	}

	//Adjust the number of chips based on the inputted integer
	void adjustChips(int num)
	{
		numChips += num;
	}

	//Returns the player's number of chips
	int getChips()
	{
		return numChips;
	}

	//Sets the values of diceArray to three inputted integers
	void setDice(int dice1, int dice2, int dice3)
	{
		diceArray[0] = dice1;
		diceArray[1] = dice2;
		diceArray[2] = dice3;
	}

	//Returns the dice value at index i
	int getDice(int i)
	{
		return diceArray[i];
	}

};