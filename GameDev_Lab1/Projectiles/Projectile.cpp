// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

// Sets default values
AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	}
	SetupCollisionComponent();
	SetupMovementComponent();
	SetupMeshComponent();
	InitialLifeSpan = LifeSpan;
	CollissionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
	CollissionComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::SetupCollisionComponent()
{
	if (!CollissionComponent)
	{
		CollissionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
		CollissionComponent->InitSphereRadius(10.0f);
		RootComponent = CollissionComponent;
	}
}

void AProjectile::SetupMovementComponent()
{
	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));
	MovementComponent->SetUpdatedComponent(RootComponent);
	MovementComponent->InitialSpeed = 3000.0f;
	MovementComponent->MaxSpeed = 3000.0f;
	MovementComponent->bRotationFollowsVelocity = true;
	MovementComponent->bShouldBounce = true;
	MovementComponent->Bounciness = 0.2f;
	MovementComponent->ProjectileGravityScale = 0.0f;
}

void AProjectile::SetupMeshComponent()
{
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);
}

void AProjectile::OnHit(
	UPrimitiveComponent* HitComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComponent,
	FVector NormalImpulse,
	const FHitResult& Hit)
{
	static const float Impulse = 100.0f;

	if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
	{
		OtherComponent->AddImpulseAtLocation(MovementComponent->Velocity * Impulse, Hit.ImpactPoint);
	}

	Destroy();
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::FireInDirection(const FVector& Direction) const
{
	MovementComponent->Velocity = Direction * MovementComponent->InitialSpeed;
}

