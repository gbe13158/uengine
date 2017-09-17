// Fill out your copyright notice in the Description page of Project Settings.

#include "PositionReport.h"

#include "GameFramework/Actor.h"


// Sets default values for this component's properties
UPositionReport::UPositionReport()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPositionReport::BeginPlay()
{
	Super::BeginPlay();
	FString ObjectName = this->GetOwner()->GetName();
	FVector Location = this->GetOwner()->GetActorLocation();
	FString ObjectPos = "X= , Y = ";
	UE_LOG(LogTemp, Warning, TEXT("%s is at X = %f, Y= %f"), *ObjectName, Location.X, Location.Y);
	UE_LOG(LogTemp, Warning, TEXT("%s is at Vec = %s"), *ObjectName, *Location.ToString());
	
}


// Called every frame
void UPositionReport::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

