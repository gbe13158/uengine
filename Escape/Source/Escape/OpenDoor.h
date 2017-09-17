// Truite copyright

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

class ATriggerVolume;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOpenRequest);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCloseEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_API UOpenDoor : public UActorComponent
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
	FOnOpenRequest onOpenRequest;

	UPROPERTY(BlueprintAssignable)
	FOnCloseEvent onCloseEvent;

private:
	

	
	UPROPERTY(EditAnywhere)
	ATriggerVolume* pressurePlate;

	UPROPERTY(EditAnywhere)
	float TriggerMass = 30.0f;


	float GetTotalMassOfActorsOnPlate();

	
};
