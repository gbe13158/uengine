// Truite copyright

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CouchInspector.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_API UCouchInspector : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCouchInspector();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	
};
