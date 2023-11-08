// Fill out your copyright notice in the Description page of Project Settings.


#include "GameDev_Lab1/Enemies/EnemyCarpenter.h"

// Sets default values
AEnemyCarpenter::AEnemyCarpenter()
{
    AEnemyCarpenter::SetupMeshComponents();
}

void AEnemyCarpenter::SetupMeshComponents()
{
	// Create and attach a gun skeletal mesh component
	ChairStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ChairStaticMeshComponent"));
	ChairStaticMeshComponent->SetupAttachment(GetMesh());	
}

// Called when the game starts or when spawned
void AEnemyCarpenter::BeginPlay()
{
	Super::BeginPlay();
	
	// Attach sword skeletal mesh to the main mesh
	ChairStaticMeshComponent->AttachToComponent(
		GetMesh(),
		FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true),
		TEXT("ChairPoint")
	);
}

// Called every frame
void AEnemyCarpenter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
