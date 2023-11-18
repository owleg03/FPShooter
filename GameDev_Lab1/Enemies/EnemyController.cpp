// Fill out your copyright notice in the Description page of Project Settings.


#include "GameDev_Lab1/Enemies/EnemyController.h"

AEnemyController::AEnemyController()
{
	PatrolRadius = 150.0f;
	PatrolTargetKey = "PatrolTarget";
}

float AEnemyController::GetPatrolRadius() const
{
	return PatrolRadius;
}

const FName& AEnemyController::GetPatrolTargetKey() const
{
	return PatrolTargetKey;
}
