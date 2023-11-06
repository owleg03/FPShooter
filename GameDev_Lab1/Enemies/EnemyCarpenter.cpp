// Fill out your copyright notice in the Description page of Project Settings.


#include "GameDev_Lab1/Enemies/EnemyCarpenter.h"

// Sets default values
AEnemyCarpenter::AEnemyCarpenter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetupChairStaticMeshComponent();
}

void AEnemyCarpenter::SetupChairStaticMeshComponent()
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

// Called to bind functionality to input
void AEnemyCarpenter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
