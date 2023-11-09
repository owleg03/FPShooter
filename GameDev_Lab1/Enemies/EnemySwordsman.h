// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "EnemySwordsman.generated.h"

UCLASS()
class GAMEDEV_LAB1_API AEnemySwordsman : public AEnemyBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemySwordsman();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* SwordStaticMeshComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	virtual void SetupMeshComponents() override;
};
