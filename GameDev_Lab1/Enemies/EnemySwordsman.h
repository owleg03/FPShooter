// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemySwordsman.generated.h"

UCLASS()
class GAMEDEV_LAB1_API AEnemySwordsman : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemySwordsman();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* SwordSkeletalMeshComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void SetupSwordSkeletalMeshComponent();
};
