// Fill out your copyright notice in the Description page of Project Settings.


#include "GameDev_Lab1/Enemies/EnemySwordsman.h"

// Sets default values
AEnemySwordsman::AEnemySwordsman()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetupSwordSkeletalMeshComponent();

}

void AEnemySwordsman::SetupSwordSkeletalMeshComponent()
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

// Called to bind functionality to input
void AEnemySwordsman::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
