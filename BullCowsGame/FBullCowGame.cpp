
#pragma once
#include "FBullCowGame.h"
#include <map>

//to make Unreal Syntax friendly
#define  TMap std::map


int32 FBullCowGame::GetCurrentTry() const{return MyCurrentTry;}
int32 FBullCowGame::GetHiddenWordLength() const{return MyHiddenWord.length();}
int32 FBullCowGame::GetMaxTries() const{
	TMap <int32, int32> WordLengthToMaxTries{ {3,4} ,{4,7} ,{5,10} ,{6,16} ,{7,20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
	}

FBullCowGame::FBullCowGame()
{
	Reset();
}

bool FBullCowGame::IsGameWon() const
{
	return bGameIsWon;
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "donkey"; //this must be an isogram
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	
	
	return;
}





EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))// if the guess isn't an isogram
	{
		return EGuessStatus::NOT_Isogram;
	}
	else if (!IsLowerCase(Guess))// if the guess isn't all lower case
	{
		return EGuessStatus::Not_Lowercase;
	}
		
	else if (Guess.length() != GetHiddenWordLength())	// if guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
	
}

//receives a valid guess , increments turn ,and returns counts
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess

	//look through all the letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		//compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			//if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				//if they are in the same place
				if (MHWChar == GChar) {
					BullCowCount.Bulls++;//increment bulls
				}
				else
				{
					BullCowCount.Cows++;//increment cows
				}	
			}
		}
	}
	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 as isogram
	if (Word.length() <= 1) { return true; }

	TMap <char, bool> LetterSeen; //setup our map
	for(auto  Letter : Word) //for all letters of the word
	{
		Letter = tolower(Letter);//handle mixed case
		if (LetterSeen[Letter]) {//if the letter is in the map
			return false;//we do NOT have an isogram
		}
		else {//else
			LetterSeen[Letter] = true;//add the letter to the map as seen
		}					
	}
	return true;
}

bool FBullCowGame::IsLowerCase(FString Word) const
{
	for (auto Letter : Word)
	{
		if(!islower(Letter))
		return false;
	}
	return true;
}
