// Fill out your copyright notice in the Description page of Project Settings.


#include "GameDev_Lab1/Enemies/SpawnEnemiesManager.h"
#include "SpawnEnemiesTargetPoint.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASpawnEnemiesManager::ASpawnEnemiesManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ASpawnEnemiesManager::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> TargetPoints;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnEnemiesTargetPoint::StaticClass(), TargetPoints);

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	for (const AActor* TargetPoint: TargetPoints)
	{
		const TSubclassOf<AEnemyBase> EnemyTypeToSpawn = PickRandomEnemyType();
		GetWorld()->SpawnActor<AEnemyBase>(EnemyTypeToSpawn, TargetPoint->GetActorTransform(), SpawnParameters);
	}
}

// Picks a random enemy type from an array
TSubclassOf<AEnemyBase> ASpawnEnemiesManager::PickRandomEnemyType()
{
	const int EnemyTypesLength = EnemyTypes.Num();
	const int RandomIndex = rand() % EnemyTypesLength;
	return EnemyTypes[RandomIndex];
}
