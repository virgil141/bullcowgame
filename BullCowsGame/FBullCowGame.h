/* the game logic (no view code or direct user interaction)
The game is a simple guess the word game based on Mastermind*/

#pragma once
#include <string>

//to make Unreal Syntax friendly
using FString = std::string;
using int32 = int;

struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus {
	Invalid_Status,
	OK,
	NOT_Isogram,
	Wrong_Length,
	Not_Lowercase
};


class FBullCowGame {
public:
	FBullCowGame(); //constructor

	void Reset();
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const; 
	
	// Provide a method counting bulls & cows , and increasing try # 
	FBullCowCount SubmitValidGuess(FString);

private:
	//see constructor for initialization
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowerCase(FString) const;
};
