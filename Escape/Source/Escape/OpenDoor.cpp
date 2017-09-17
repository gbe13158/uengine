// Truite copyright

#include "OpenDoor.h"

#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Engine/TriggerVolume.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"


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

}



// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (GetTotalMassOfActorsOnPlate() > TriggerMass)
	{
		onOpenRequest.Broadcast();
	}
	else 
	{
		onCloseEvent.Broadcast();
	}
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float totalMass = 0.0f;
	TSet<AActor*> overlapingActors;
	pressurePlate->GetOverlappingActors(overlapingActors);
	TSet<AActor*>::TIterator overlapingActorsIterator = overlapingActors.CreateIterator();
	for (const auto* actor : overlapingActors)
	{
		totalMass += actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	return totalMass;
}

	