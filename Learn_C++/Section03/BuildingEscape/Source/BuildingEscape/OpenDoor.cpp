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

void UOpenDoor::OpenDoor() 
{
	Owner->SetActorRotation(FRotator(0.0f, DoorOpenAngle, 0.0f));
}

void UOpenDoor::CloseDoor() 
{
	Owner->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) 
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if ((TotalMassOfActorsOnPressurePlate() > TriggerMass) && (TotalMassOfActorsOnPressurePlate() < OverMass)) //Mass must be between 49.9 and 54
	{
		OpenDoor();
		DoorLastOpenTime = GetWorld()->GetTimeSeconds();
	}

	//CloseDoor Timer
	if (GetWorld()->GetTimeSeconds() - DoorCloseDelay > DoorLastOpenTime)
	{
		CloseDoor();
	}
	
}

float UOpenDoor::TotalMassOfActorsOnPressurePlate()
{
	float TotalMass = 0.f;
	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OverlappingActors);
	
	for (const auto& Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return TotalMass;
}

