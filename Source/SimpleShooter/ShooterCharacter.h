// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Engine/TriggerVolume.h"


#include "ShooterCharacter.generated.h"
class AGun;
class UOpenDoor;
UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	void Shoot();
	void Interact();
private:
	void MoveForward(float AxisValue);
	void MoveLeft(float AxisValue);

	void LookUp(float AxisValue);
	void LookLeft(float AxisValue);

	void LookUpRate(float AxisValue);
	void LookRightRate(float AxisValue);



	UPROPERTY(EditAnywhere)
	float RotationRate = 10.0f;

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100.0f;

	UPROPERTY(VisibleAnywhere)
	float Health;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass; // not a pointer since its a class

	UPROPERTY()
	AGun *Gun;

	// UPROPERTY(EditDefaultsOnly)
	// TSubclassOf<UOpenDoor> DoorClasss;

	// UPROPERTY()
	// UOpenDoor *OpenDoor;

	// UPROPERTY(EditAnyWhere)
	// ATriggerVolume *PressurePlate;

	float Reach {500.f};

};
