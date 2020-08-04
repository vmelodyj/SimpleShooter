// Fill out your copyright notice in the Description page of Project Settings.


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

	InitialYaw = GetOwner()->GetActorRotation().Yaw;	
	CurrentYaw = InitialYaw;
	OpenAngle += InitialYaw;

	UE_LOG(LogTemp, Warning, TEXT("Current Yaw is %f"), CurrentYaw);
	// 
	// ...
	
}

// 
// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// OpenDoor(DeltaTime);

	// ...

	// UE_LOG(LogTemp, Warning, TEXT("Current Yaw is %f"));
	// CurrentYaw = FMath::FInterpConstantTo(CurrentYaw, OpenAngle, GetWorld()->GetDeltaSeconds(),45);	
	// FRotator DoorRotation = GetOwner()->GetActorRotation();
	// DoorRotation.Yaw = CurrentYaw;
	// GetOwner()->SetActorRotation(DoorRotation);
	if (DoorNeedsToOpen) {
	CurrentYaw = FMath::FInterpConstantTo(CurrentYaw, OpenAngle, GetWorld()->GetDeltaSeconds(),90);	
	// UE_LOG(LogTemp, Warning, TEXT("Current Yaw is %f"), CurrentYaw);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);
	} else {
	CurrentYaw = FMath::FInterpConstantTo(CurrentYaw, InitialYaw, GetWorld()->GetDeltaSeconds(),90);	
	// UE_LOG(LogTemp, Warning, TEXT("Current Yaw is %f"), CurrentYaw);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);		
	}
}

void UOpenDoor::OpenDoor() 
{
	DoorNeedsToOpen = !DoorNeedsToOpen;
}


	