// Copyright Jarrod Shaw & Metal Muffin Ent. 2018

#include "OpenDoor.h"
#include "GameFramework/Actor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor() 
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay() 
{
	Super::BeginPlay();

	Owner = GetOwner();
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) 
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TotalMassOfActorsOnPressurePlate() > TriggerMass) 
	{
		OnOpenDoorRequest.Broadcast();
	}
	else
	{
		OnCloseDoorRequest.Broadcast();
	}
}

float UOpenDoor::TotalMassOfActorsOnPressurePlate()
{
	float TotalMass = 0.f;
	TArray<AActor*> OverlappingActors;
	if (!PressurePlate) { return TotalMass; }
	PressurePlate->GetOverlappingActors(OverlappingActors);
	
	for (const auto& Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return TotalMass;
}

