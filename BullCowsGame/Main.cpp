/* This is the console executable , that makes the use of BullCows class
this act as the view in a MVC patten , and is responsible for all user interactions.
for the game logic see the FBullCowGame class.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

//to make Unreal Syntax friendly
using FText = std::string;
using int32 = int;

//function prototypes as outside a class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCgame; // instantiate a new game , which we re-use across plays


//entry of the program
int main()
{
	std::cout << BCgame.GetCurrentTry();
	bool bWantsToPlayAgain = false;
	do 
	{
		PrintIntro();
		PlayGame();
		bWantsToPlayAgain = AskToPlayAgain();
	} while (bWantsToPlayAgain == true);
	
	return 0;//exit game
}

//plays a single game to completion
void PlayGame()
{
	BCgame.Reset();
	int32 MaxTries = BCgame.GetMaxTries();
	//loop asking for guess until the game
	//is NOT won and there are still tries remaining
	while ( !BCgame.IsGameWon() && BCgame.GetCurrentTry() <= MaxTries )
	{
		FText Guess = GetValidGuess();

		//submit valid guess to the game
		FBullCowCount BullCowCount = BCgame.SubmitValidGuess(Guess);

		//print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}
	PrintGameSummary();
	return;
}


//introduce the game to the player
void PrintIntro() 
{
	std::cout << "Welcome to Bulls and Cows,a fun game.\n";
	std::cout << "           }   {          ____ " << std::endl;
	std::cout << "           (o  o)        (o  o) " << std::endl;
	std::cout << "    /-------\\ /           \\ / -------\\ " << std::endl;
	std::cout << "   / | BULL |O             O| COW |   \\" << std::endl;
	std::cout << "  *  |-,--- |               |-----|    *" << std::endl;
	std::cout << "     ^      ^               ^     ^   " << std::endl;
	std::cout << "Can you guess the " << BCgame.GetHiddenWordLength();
	std::cout << " letter histogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

//loop continually until get a valid guess
FText GetValidGuess() 
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";

	do {
		int32 CurrentTry = BCgame.GetCurrentTry();

		std::cout << "Try " << CurrentTry << " of " << BCgame.GetMaxTries()<<".Enter your guess: ";
		
		getline(std::cin, Guess);

		 Status = BCgame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCgame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::NOT_Isogram:
			std::cout << "Please enter a letter without repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lower case letters.\n\n";
			break;
		default:
			//assuming the guess is valid
			break;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK); //keep looping until we get valid input
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same word?(y/n)" << std::endl;
	FText Response = "";
	getline(std::cin, Response);
	return (Response[0] == 'y' || Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCgame.IsGameWon())
	{
		std::cout << "WELL DONE !! YOU WIN!!\n";
	}
	else
	{
		std::cout << "Better luck next time!\n";
	}
}
