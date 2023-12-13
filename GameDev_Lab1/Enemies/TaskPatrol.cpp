// Fill out your copyright notice in the Description page of Project Settings.


#include "GameDev_Lab1/Enemies/TaskPatrol.h"

#include "AIController.h"
#include "EnemyController.h"
#include "EnemySwordsman.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UTaskPatrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyController* EnemyController = Cast<AEnemyController>(OwnerComp.GetAIOwner());
	const float PatrolRadius = EnemyController->GetPatrolRadius();
	if (PatrolRadius <= 0)
	{
		return EBTNodeResult::Failed;
	}
	
	FNavLocation ResultLocation;
	const UNavigationSystemV1* NavigationSystemV1 = UNavigationSystemV1::GetNavigationSystem(&OwnerComp);
	const FVector EnemyLocation = EnemyController->GetNavAgentLocation();
	const bool bIsPointFoundSuccessfully = NavigationSystemV1->
		GetRandomReachablePointInRadius(
			EnemyLocation,
			PatrolRadius,
			ResultLocation);
	
	if (bIsPointFoundSuccessfully)
	{
		EnemyController->GetBlackboardComponent()->SetValueAsVector(
			EnemyController->GetPatrolTargetKey(),
			ResultLocation.Location);

		if (WalkAnimation)
		{
			APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn();
			const AEnemySwordsman* EnemySwordsman = Cast<AEnemySwordsman>(Pawn);
			EnemySwordsman->GetMesh()->PlayAnimation(WalkAnimation, true);
		}
		
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
