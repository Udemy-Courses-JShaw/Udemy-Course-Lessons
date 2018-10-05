// Copyright Jarrod Shaw & Metal Muffin Ent. 2018

#include "Grabber.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Runtime/Core/Public/Math/Vector.h"


// Sets default values for this component's properties
UGrabber::UGrabber() 
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay() 
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber Reporting In!!"));

}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) 
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Get Player Vew point this/every tick
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint( PlayerLocation, PlayerRotation ); 

	//To log to test
	UE_LOG(LogTemp, Warning, TEXT("Player Info - Location: %s , Rotation: %s"), *PlayerLocation.ToString(), *PlayerRotation.ToString());
	// Ray-cast out to reach distance

	// see what we hit
}

