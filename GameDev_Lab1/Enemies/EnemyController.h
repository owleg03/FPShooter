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
	
public:
	AEnemyController();
	
	float GetPatrolRadius() const;
	const FName& GetPatrolTargetKey() const;
};
