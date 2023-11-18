// Fill out your copyright notice in the Description page of Project Settings.


#include "GameDev_Lab1/Enemies/EnemySwordsman.h"

// Sets default values
AEnemySwordsman::AEnemySwordsman()
{
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

}

// Called when another actor is spotted
void AEnemySwordsman::OnActorPerceived(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed())
	{
		PerceivedActor = Actor;
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
