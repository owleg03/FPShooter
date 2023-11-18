// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameDev_Lab1/Common/PlayerTeamId.h"
#include "GameDev_Lab1/Projectiles/Projectile.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

UCLASS()
class GAMEDEV_LAB1_API AMainCharacter : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* GunSkeletalMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector MuzzleOffset;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int AmmoCount;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Handles forward/backward movement
	UFUNCTION()
	void MoveForward(float Value);

	// Handles right/left movement
	UFUNCTION()
	void MoveRight(float Value);

	// Handles jump start
	UFUNCTION()
	void StartJump();

	// Handles jump end
	UFUNCTION()
	void EndJump();

	// Handles crouch start
	UFUNCTION()
	void StartCrouch();

	// Handles crouch end
	UFUNCTION()
	void EndCrouch();

	// Handles turning around
	UFUNCTION()
	void TurnAround();

	// Handles firing a weapon
	UFUNCTION(BlueprintCallable)
	void Fire();

	// Identifies the player's team
	virtual FGenericTeamId GetGenericTeamId() const override;

private:
	void SetupCameraComponent();
	void SetupGunSkeletalMeshComponent();
	FPlayerTeamId TeamId;
};
