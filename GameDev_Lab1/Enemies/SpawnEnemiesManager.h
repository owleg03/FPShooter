// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemySwordsman.h"
#include "GameFramework/Actor.h"
#include "SpawnEnemiesManager.generated.h"

UCLASS()
class GAMEDEV_LAB1_API ASpawnEnemiesManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnEnemiesManager();

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AEnemyBase>> EnemyTypes;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Picks a random enemy type from an array
	TSubclassOf<AEnemyBase> PickRandomEnemyType();
};
