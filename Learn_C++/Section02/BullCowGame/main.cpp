/*
Tnis is the Consoel Executable that makes use of BullCow Class
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For Game logic see the FBullCow class
*/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

//substitutions to make syntax more UREAL Engine 4 friendly
using FText = std::string;
using int32 = int;

//Prototypes outside class
void DisplayIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();


FBullCowGame BCGame; //instanciate a new game, which we reuse across plays


//ENTRY POINT FOR APPLICATION****************************************
int main() {

	//Intros Game
	DisplayIntro();
	bool bPlayAgain = false;
	do {
		//Play game:
		PlayGame();
		
		//Want to replay?
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);
	return 0; //Exits he app
}

// Single playthrough of a game, looped in main()
void PlayGame() {
	bool IsPlaying = true; //set to false to end game
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	int32 Tries = BCGame.GetCurrentTry();

	std::cout << "You have " << Tries << " tries to guess the word!" << std::endl;
	// Asking for guesses while game 
	//is *NOT* won and Tries are still remaining
	while (!BCGame.GetIsGameWon() && BCGame.GetCurrentTry() <= MaxTries) { 
		FText Guess = GetValidGuess();
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);		// print number of Bulls And Cows
		std::cout << "Bulles = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
		std::cout << "Number of Tries: " << BCGame.GetCurrentTry() << std::endl;
		
	}
	
	PrintGameSummary();

	return;
}

// Loop until playet gives a vaid guess
FText GetValidGuess() {
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";
		do {
			std::cout << "Try " << BCGame.GetCurrentTry() << " of " << BCGame.GetMaxTries();
			std::cout << ": What is your Guess ? "; // Tell player how many tries they have left
		std::getline(std::cin, Guess);	//get input from player
		Status = BCGame.CheckGuessValidity(Guess);		//Verifies word is valid
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word! \n";
			break;
		case EGuessStatus::Contains_Number:
			std::cout << "Your Guess cannot contain a number! \n";
			break;
		case EGuessStatus::Contains_Space:
			std::cout << "Your guess cannot contain a space! \n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please Guess a Word that does NOT contain repeating letters! \n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please use lower case letters only! \n";
			break;
		default:
			// assume the guess is valid
			break;
			}
		}while (Status != EGuessStatus::OK);
	
	return Guess;
}


bool AskToPlayAgain() {

	//Ask if the want to play again
	std::cout << "Would you like to play again?  Y/N?\n" << std::endl;
	FText Responce = "";
	std::getline(std::cin, Responce);

	return (Responce[0] == 'Y') || (Responce[0] == 'y');
}

//Displays the into for the game
void DisplayIntro() {

	// Introduce game
	std::cout << "Welcome to Bulls and Cows Game!\n" << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram word I'm thinking?" << std::endl;
	std::cout << "You will have " << BCGame.GetMaxTries() << " tries to guess the word! \n GoodLuck! " << std::endl << std::endl;
	std::cout << "BULL = Letter is in the word and is in the correct place!\n";
	std::cout << "COW = Letter is in the word, but IS NOT in the corect place\n";
	std::cout << std::endl;

	return;
}

void PrintGameSummary() {
	if (BCGame.GetIsGameWon()) {
		std::cout << "You have WON!! \n\nCONGRATULATIONS!" << std::endl;
	}
	else {
		std::cout << "Sorry!! \n\n Better Luck next time." << std::endl;
	}
	return;
}