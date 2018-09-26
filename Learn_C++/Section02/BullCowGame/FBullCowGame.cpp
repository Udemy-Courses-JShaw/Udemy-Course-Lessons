#pragma once
#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using int32 = int;

FBullCowGame::FBullCowGame() {
	Reset();
	return;
}

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
bool FBullCowGame::GetIsGameWon() const { return b_IsGameWon; }

int32 FBullCowGame::GetMaxTries() const { 
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,15}, {7,20} };
	return static_cast<int32>(WordLengthToMaxTries[MyHiddenWord.length()]); 
}


int32 FBullCowGame::GetHiddenWordLength() const {
	return static_cast<int32>(MyHiddenWord.length());
}

void FBullCowGame::Reset() {

	const FString HIDDEN_WORD = "planet";
	MyHiddenWord = HIDDEN_WORD;
	SetIsGameWon(false);
	MyCurrentTry = 1;
	return;
}

void FBullCowGame::SetIsGameWon(bool b_IsGameWonl) {
	b_IsGameWon = b_IsGameWonl;
	//Input -> sets Private bool
}

//Checks to see if the guess is within parameters
EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const {
	if (!IsIsogram(Guess) ) {	
		return EGuessStatus::Not_Isogram; 
	}
	else if (GetHiddenWordLength() != Guess.length() ) {	
		return EGuessStatus::Wrong_Length;
	}
	else if (IsLowerCase(Guess) ) {	
		return EGuessStatus::Not_Lowercase;   
	}
	else if (HasNoNumber(Guess) ) {	
		return EGuessStatus::Contains_Number; 
	}
	else if (HasNoSpace(Guess) ) {	
		return EGuessStatus::Contains_Space;  
	}
	else {
		return EGuessStatus::OK;
	}

}

// Recieves a valid guss, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess) {
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	// loop through all letters in the Hidden word
	int32 WordLength = static_cast<int32>(MyHiddenWord.length());
	// assume hidden word and guess are same length
	for (int32 MHWChar = 0; MHWChar <= WordLength; MHWChar++) {	
		// Compare letters against guess
		for (int32 GChar = 0; GChar <= WordLength; GChar++) {
			// If thy match then
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				// If they are in the same place
				if (MHWChar == GChar) {
				// Increment Bulls if they are in the same place
				BullCowCount.Bulls++;
				}
				else {
				// Increment Cows if not
				BullCowCount.Cows++;
				}
				
			}

		}
			
	}
	if (BullCowCount.Bulls >= static_cast<int32>(MyHiddenWord.length())) {
		SetIsGameWon(true);
	}
	else {
		SetIsGameWon(false);
	}
	
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Guess) const {
	//Treat 1 and 0 letter words as isograms
	if (Guess.length() <= 1) { return true; }
	
	TMap<char, bool> LetterSeen;
	for(auto Letter : Guess){
		Letter = tolower(Letter); 
		if (LetterSeen[Letter]) {
			return false;
		} else {
		LetterSeen[Letter] = true;
			}
		}
	return true;
}


bool FBullCowGame::IsLowerCase(FString Guess) const {
	for (auto Letter : Guess) {
		if (isupper(Letter)) {
			return true;
		}
	}
	return false;
}

bool FBullCowGame::HasNoNumber(FString Guess) const {
	for (auto Letter : Guess) {
		if (isdigit(Letter)) {
			return true;
		}
	}
	return false;
}

bool FBullCowGame::HasNoSpace(FString Guess) const {
	for (auto Letter : Guess) {
		if (isspace(Letter)) {
			return true;
		}
	}
	return false;
}
