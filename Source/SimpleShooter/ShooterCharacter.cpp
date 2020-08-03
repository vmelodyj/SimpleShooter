// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "Gun.h"
#include "OpenDoor.h"
#include "Components/CapsuleComponent.h"
#include "SimpleShooterGameModeBase.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h" // test for draw debug line, prepare for the linetrace

#include "GameFramework/PlayerController.h"


// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun->SetOwner(this);
	
}

bool AShooterCharacter::IsDead() const
{
	return (Health <= 0);
}

float AShooterCharacter::GetHealthPercent() const
{
	return Health / MaxHealth;
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AShooterCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &AShooterCharacter::LookUpRate);

	PlayerInputComponent->BindAxis(TEXT("MoveLeft"), this, &AShooterCharacter::MoveLeft);
	PlayerInputComponent->BindAxis(TEXT("LookLeft"), this, &AShooterCharacter::LookLeft);
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &AShooterCharacter::LookRightRate);

	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACharacter::Jump);

	PlayerInputComponent->BindAction(TEXT("Shoot"), IE_Pressed, this, &AShooterCharacter::Shoot);

	PlayerInputComponent->BindAction(TEXT("Interact"), IE_Pressed, this, &AShooterCharacter::Interact);



}

float AShooterCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) 
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(Health, DamageToApply);
	Health -= DamageToApply;

	UE_LOG(LogTemp, Warning, TEXT("Health left %f"), Health);

	if (IsDead()){
		
		// Now call the gamemode
		ASimpleShooterGameModeBase *GameMode = GetWorld()->GetAuthGameMode<ASimpleShooterGameModeBase>();
		if (GameMode != nullptr) {
			GameMode->PawnKilled(this);
		}
		// If the player has died, take away its controller
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);



	}


	return DamageToApply;
}

void AShooterCharacter::MoveForward(float AxisValue) 
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AShooterCharacter::MoveLeft(float AxisValue) 
{
	AddMovementInput(GetActorRightVector() * (-AxisValue));
}

void AShooterCharacter::LookUp(float AxisValue) 
{
	AddControllerPitchInput(AxisValue);
}

void AShooterCharacter::LookLeft(float AxisValue) 
{
	AddControllerYawInput(-AxisValue);
}

void AShooterCharacter::LookUpRate(float AxisValue) 
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::LookRightRate(float AxisValue) 
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::Shoot() 
{
	// UE_LOG(LogTemp, Warning, TEXT("test"));
	Gun->PullTrigger();
}

void AShooterCharacter::Interact() 
{	
	// if (OpenDoor != nullptr){
	// UE_LOG(LogTemp, Warning, TEXT("test in interact"));
	// OpenDoor->OpenDoor();
	// } else {
	// 	UE_LOG(LogTemp, Warning, TEXT("test in interact failed"));
	// }


	// Do a line trace here, if it hits something, cast that to UOpenDoor, if it succeed then call OpenDoor()
	FVector PlayerLocation;
	FRotator PlayerRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerLocation,PlayerRotation);
	UE_LOG(LogTemp, Warning, TEXT("The player location is: %s, rotation is: %s"), 
	*PlayerLocation.ToString(), 
	*PlayerRotation.ToString());

	FVector LineTraceEnd = PlayerLocation + PlayerRotation.Vector() * Reach;
	FHitResult Hit;

	FCollisionQueryParams TraceParams(FName(TEXT("")), false, this);
	GetWorld()->LineTraceSingleByObjectType(
		Hit,
		PlayerLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);
	AActor* ActorHit = Hit.GetActor();
	
	if (ActorHit) {
		// Call OpenDoor->Opendoor();
		UE_LOG(LogTemp, Warning, TEXT("Has hit %s"), *(ActorHit->GetName()));
	}


}

