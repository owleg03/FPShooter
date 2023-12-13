// Fill out your copyright notice in the Description page of Project Settings.


#include "GameDev_Lab1/Enemies/EnemyController.h"

AEnemyController::AEnemyController()
{
	PatrolRadius = 150.0f;
	PatrolTargetKey = "PatrolTarget";
	HasLineOfSightKey = "HasLineOfSight";
	DetectedEnemyKey = "DetectedEnemy";
	IsObstacleDetectedKey = "IsObstacleDetected";
	LastKnownLocationKey = "LastKnownLocation";
}

float AEnemyController::GetPatrolRadius() const
{
	return PatrolRadius;
}

const FName& AEnemyController::GetPatrolTargetKey() const
{
	return PatrolTargetKey;
}

const FName& AEnemyController::GetHasLineOfSightKey() const
{
	return HasLineOfSightKey;
}

const FName& AEnemyController::GetDetectedEnemyKey() const
{
	return DetectedEnemyKey;
}

const FName& AEnemyController::GetIsObstacleDetectedKey() const
{
	return IsObstacleDetectedKey;
}

const FName& AEnemyController::GetLastKnownLocationKey() const
{
	return LastKnownLocationKey;
}
