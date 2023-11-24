// Fill out your copyright notice in the Description page of Project Settings.


#include "GameDev_Lab1/Enemies/EnemySwordsman.h"

#include "AIController.h"
#include "EnemyController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AEnemySwordsman::AEnemySwordsman()
{
	bIsRunning = true;
	bHasLineOfSight = false;
	TargetLostElapsed = 0.f;
	LastLocationElapsed = 0.f;
	LastLocationUpdateTime = 0.5f;
	
    AEnemySwordsman::SetupMeshComponents();
	
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));
}

void AEnemySwordsman::SetupMeshComponents()
{
	SwordStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SwordStaticMeshComponent"));
	SwordStaticMeshComponent->SetupAttachment(GetMesh());
}


// Called when the game starts or when spawned
void AEnemySwordsman::BeginPlay()
{
	Super::BeginPlay();
	
	RunningSpeed = GetCharacterMovement()->MaxWalkSpeed;
	WalkingSpeed = RunningSpeed / 4;
	EnemyController = Cast<AEnemyController>(Controller);
	

	// Attach gun skeletal mesh to the main mesh
	SwordStaticMeshComponent->AttachToComponent(
		GetMesh(),
		FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true),
		TEXT("SwordSocket")
	);

	// Subscribe to perception event
	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemySwordsman::OnActorPerceived);
}

// Called every frame
void AEnemySwordsman::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bHasLineOfSight && (LastLocationElapsed += DeltaTime) >= LastLocationUpdateTime)
	{
		LastLocationElapsed = 0.f;
		EnemyController->GetBlackboardComponent()->SetValue<UBlackboardKeyType_Vector>(
			EnemyController->GetLastKnownLocationKey(), PerceivedActor->GetActorLocation());
	}

	if (!bHasLineOfSight && PerceivedActor && (TargetLostElapsed += DeltaTime) >= TargetLostTime)
	{
		PerceivedActor = nullptr;
		TargetLostElapsed = 0.f;
		EnemyController->GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(
			EnemyController->GetDetectedObjectKey(), PerceivedActor);
	}
}

// Called when another actor is spotted
void AEnemySwordsman::OnActorPerceived(AActor* Actor, FAIStimulus Stimulus)
{
	bHasLineOfSight = Stimulus.WasSuccessfullySensed();

	EnemyController->GetBlackboardComponent()->SetValue<UBlackboardKeyType_Bool>(
		EnemyController->GetHasLineOfSightKey(), bHasLineOfSight);
	
	if (bHasLineOfSight)
	{
		PerceivedActor = Actor;
		TargetLostElapsed = 0.f;
		EnemyController->GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(EnemyController->GetDetectedObjectKey(), PerceivedActor);
		EnemyController->GetBlackboardComponent()->SetValue<UBlackboardKeyType_Vector>(EnemyController->GetLastKnownLocationKey(), PerceivedActor->GetActorLocation());
	}
}

// Identifies enemy's team
FGenericTeamId AEnemySwordsman::GetGenericTeamId() const
{
	return TeamId.GetId();
}

// Specifies enemy's attitude towards an actor
ETeamAttitude::Type AEnemySwordsman::GetTeamAttitudeTowards(const AActor& Other) const
{
	const IGenericTeamAgentInterface* OtherTeamAgent = Cast<const IGenericTeamAgentInterface>(&Other);
	const ETeamAttitude::Type Temp = OtherTeamAgent && OtherTeamAgent->GetGenericTeamId().GetId() == PlayersTeam ?
		ETeamAttitude::Hostile :
		ETeamAttitude::Neutral;
	return Temp;
}

// Switches movement speed to running speed
void AEnemySwordsman::SwitchToRunningSpeed()
{
	bIsRunning = true;
	GetCharacterMovement()->MaxWalkSpeed = RunningSpeed;
}

// Switches movement speed to walking speed
void AEnemySwordsman::SwitchToWalkingSpeed()
{
	bIsRunning = false;
	GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
}
