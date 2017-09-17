// Truite copyright

#include "Grabber.h"
#include "Engine/World.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	inputComponent = nullptr;
	physicsHandle = nullptr;
	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	LoadPhysicsHandle();
	LoadInputComponent();
}

void UGrabber::LoadInputComponent()
{
	inputComponent = this->GetOwner()->FindComponentByClass<UInputComponent>();
	if (!inputComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Unable to find inputComponents on %s"), *(GetOwner()->GetName()))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("InputComponent found on %s"), *(GetOwner()->GetName()))
			inputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		inputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
}

void UGrabber::LoadPhysicsHandle()
{
	physicsHandle = this->GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!physicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("Unable to find physicsHandle on %s"), *(GetOwner()->GetName()))
	}
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (physicsHandle->GrabbedComponent)
	{
		FVector location;
		FRotator rotation;
		GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(location, rotation);

		FVector lineTraceEnd = location + rotation.Vector()*GrabDistance;
		physicsHandle->SetTargetLocation(lineTraceEnd);
	}

}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab released"));
	physicsHandle->ReleaseComponent();
}
void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab pressed"));
	FHitResult hitResult = GetFirstPhysicsBodyInReach();
	if (hitResult.GetActor())
	{
		UPrimitiveComponent* componentToGrab = hitResult.GetComponent();
		physicsHandle->GrabComponent(componentToGrab, NAME_None, componentToGrab->GetOwner()->GetActorLocation(), true);
	}
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	FVector location;
	FRotator rotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(location, rotation);

	FVector lineTraceEnd = location + rotation.Vector()*GrabDistance;
	FHitResult hit;
	FCollisionObjectQueryParams objectParams(ECollisionChannel::ECC_PhysicsBody);
	FCollisionQueryParams queryParams(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(hit, location, lineTraceEnd, objectParams, queryParams);
	AActor* hitActor = hit.GetActor();
	if (hitActor != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("found something to grab : %s"), *hitActor->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Nothing to grab !"));
	}
	return hit;
}

