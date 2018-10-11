// Copyright Jarrod Shaw & Metal Muffin Ent. 2018

#include "Grabber.h"
#include "Components/PrimitiveComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Math/Vector.h"


// Sets default values for this component's properties
UGrabber::UGrabber() 
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay() 
{
	Super::BeginPlay();

	FindPhysicsHandleComponent();
	SetupInputComponent();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) 
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	FVector PlayerViewPortLocation; //Player Location X,Y,Z
	FRotator PlayerViewPortRotation; //Plyer Rotation in degrees
									 /// Get Player View point this tick
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint( PlayerViewPortLocation, PlayerViewPortRotation ); 
	FVector LineTraceEnd = PlayerViewPortLocation + PlayerViewPortRotation.Vector() *Reach;
	
	// if Physics Handle is atached
	if (PhysicsHandle->GrabbedComponent)
	{
		//Move the object we are holding
		PhysicsHandle->SetTargetLocation(LineTraceEnd);
	}


}

///Look for attached Physics Handle
void UGrabber::FindPhysicsHandleComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Grabbed!!"), *GetOwner()->GetName())
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing Physics Handle Component!!"), *GetOwner()->GetName())
	}
}

///Look for attached Input Component
void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found an Input Component!!"))
			///Bind Input Access
			InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::GrabRelease);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing an Input Component!!"), *GetOwner()->GetName())
	}
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Pressed Grab!"))
	/// Try to reach any actor with physics body collision channel set
	auto HitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();

	/// If we hit something attach a physic handle
	if (ActorHit)
	{
		PhysicsHandle->GrabComponent(
			ComponentToGrab,
			NAME_None,
			ComponentToGrab->GetOwner()->GetActorLocation(),
			true //true = constrains rotation (less flopping around!)
			);
	}
}

void UGrabber::GrabRelease()
{
	//UE_LOG(LogTemp, Warning, TEXT("Grabber Released!!"))
	PhysicsHandle->ReleaseComponent();
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	FVector PlayerViewPortLocation; //Player Location X,Y,Z
	FRotator PlayerViewPortRotation; //Plyer Rotation in degrees
	/// Get Player View point this tick
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint( PlayerViewPortLocation, PlayerViewPortRotation ); 
	FVector LineTraceEnd = PlayerViewPortLocation + PlayerViewPortRotation.Vector() *Reach;

	/// Setup Params
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
	// see what we hit
	AActor* ActorHit = Hit.GetActor();
	
	return Hit;
}