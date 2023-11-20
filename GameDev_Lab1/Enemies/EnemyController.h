// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyController.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDEV_LAB1_API AEnemyController : public AAIController
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float PatrolRadius;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FName PatrolTargetKey;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FName HasLineOfSightKey;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FName DetectedObjectKey;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FName LastKnownLocationKey;
	
public:
	AEnemyController();
	
	float GetPatrolRadius() const;
	const FName& GetPatrolTargetKey() const;
	const FName& GetHasLineOfSightKey() const;
	const FName& GetDetectedObjectKey() const;
	const FName& GetLastKnownLocationKey() const;
};
