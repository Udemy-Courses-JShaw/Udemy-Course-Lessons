// Copyright Jarrod Shaw & Metal Muffin Ent. 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Grabber.generated.h" //MUST be last on list!!


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDINGESCAPE_API UGrabber : public UActorComponent 
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	FVector PlayerViewPortLocation; //Player Location X,Y,Z
	FRotator PlayerViewPortRotation; //Plyer Rotation in degrees
	float Reach = 100.f; //Reach vector

};
