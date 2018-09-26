#pragma once
#include <string>

using FString = std::string;
using int32 = int;

// intialised to 0
struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus {
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase,
	Contains_Number,
	Contains_Space,
};

class FBullCowGame {
public:
	FBullCowGame(); //Constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool GetIsGameWon() const;

	EGuessStatus CheckGuessValidity(FString) const; 

	void Reset(); 
	void SetIsGameWon(bool);
	FBullCowCount SubmitValidGuess(FString);

private:
	//Initialized in constructor
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool b_IsGameWon;

	bool IsIsogram(FString) const;
	bool IsLowerCase(FString) const;
	bool HasNoNumber(FString) const;
	bool HasNoSpace(FString) const;
};
