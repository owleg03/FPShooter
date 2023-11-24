// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "EnemyController.h"
#include "GameDev_Lab1/Common/EnemyTeamId.h"
#include "Perception/AIPerceptionComponent.h"
#include "EnemySwordsman.generated.h"

UCLASS()
class GAMEDEV_LAB1_API AEnemySwordsman : public AEnemyBase, public IGenericTeamAgentInterface
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
	
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAcces = "true"))
	UAIPerceptionComponent*	PerceptionComponent;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	AActor* PerceivedActor;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	float RunningSpeed;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	float WalkingSpeed;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool bIsRunning;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool bHasLineOfSight;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float TargetLostTime;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called when another actor is spotted
	UFUNCTION()
	void OnActorPerceived(AActor* Actor, FAIStimulus Stimulus);

	// Identifies enemy's team
	UFUNCTION()
	virtual FGenericTeamId GetGenericTeamId() const override;

	// Specifies enemy's attitude towards an actor
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

	// Switches movement speed to running speed
	UFUNCTION(BlueprintCallable)
	void SwitchToRunningSpeed();
	
	UFUNCTION(BlueprintCallable)
	// Switches movement speed to walking speed
	void SwitchToWalkingSpeed();

private:
	virtual void SetupMeshComponents() override;
	FEnemyTeamId TeamId;
	float TargetLostElapsed;
	float LastLocationElapsed;
	float LastLocationUpdateTime;
	
	AEnemyController* EnemyController;
};
