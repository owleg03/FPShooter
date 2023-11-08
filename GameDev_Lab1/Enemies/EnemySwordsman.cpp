// Fill out your copyright notice in the Description page of Project Settings.


#include "GameDev_Lab1/Enemies/EnemySwordsman.h"

// Sets default values
AEnemySwordsman::AEnemySwordsman()
{
    AEnemySwordsman::SetupMeshComponents();
}

void AEnemySwordsman::SetupMeshComponents()
{
	SwordSkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SwordSkeletalMeshComponent"));
	SwordSkeletalMeshComponent->SetupAttachment(GetMesh());
}


// Called when the game starts or when spawned
void AEnemySwordsman::BeginPlay()
{
	Super::BeginPlay();

	// Attach gun skeletal mesh to the main mesh
	SwordSkeletalMeshComponent->AttachToComponent(
		GetMesh(),
		FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true),
		TEXT("SwordSocket")
	);
}

// Called every frame
void AEnemySwordsman::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}