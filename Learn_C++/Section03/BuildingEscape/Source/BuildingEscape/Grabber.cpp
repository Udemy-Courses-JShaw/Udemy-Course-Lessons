// Copyright Jarrod Shaw & Metal Muffin Ent. 2018

#include "Grabber.h"
#include "DrawDebugHelpers.h"
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
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint( PlayerViewPortLocation, PlayerViewPortRotation ); 
	FVector LineTraceEnd = PlayerViewPortLocation + PlayerViewPortRotation.Vector() *Reach;
	DrawDebugLine(
		GetWorld(),
		PlayerViewPortLocation,
		LineTraceEnd,
		FColor(255, 0, 0),
		false,
		0.f,
		0.f,
		10.f
	);
	// Setup Params
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	/// Ray-cast out to reach distance
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		Hit,  //OUT !!
		PlayerViewPortLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);
	AActor* ActorHit = Hit.GetActor();
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor HIT: %s"), *(ActorHit->GetName()));
	}
	// see what we hit
}

