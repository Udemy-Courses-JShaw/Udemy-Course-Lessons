// Copyright Jarrod Shaw & Metal Muffin Ent. 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/TriggerVolume.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "OpenDoor.generated.h" //MUST be last on list

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvents);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent 
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable)
	FDoorEvents OnOpenDoorRequest;

	UPROPERTY(BlueprintAssignable)
	FDoorEvents OnCloseDoorRequest;

private:
	
	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr;
	
	UPROPERTY(EditAnywhere)
	float TriggerMass = 49.9f; 

	//Owner for Door
	AActor *Owner = nullptr; 

	float TotalMassOfActorsOnPressurePlate();
};
