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

	DirectionNormal = FVector::ZeroVector;
	SpiralAngle = 0.0f;
	SpiralDeviation = 20.0f;
	SpiralSpeed = 15.0f;
	CurrentTick = 0.0f;
	
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
	MovementComponent->InitialSpeed = 100.0f;
	MovementComponent->MaxSpeed = 100.0f;
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
	++CurrentTick;

	// Not yet fired
	if (DirectionNormal == FVector::ZeroVector)
	{
		return;
	}

	const float SpiralY = SpiralDeviation * FMath::Cos(SpiralAngle);
	const float SpiralZ = SpiralDeviation * FMath::Sin(SpiralAngle);
	const FMatrix Rotation = FRotationMatrix(GetActorRotation());
	const FVector Position = Rotation.TransformPosition(FVector(0.0f, SpiralY, SpiralZ));
	const FVector Direction = DirectionNormal * MovementComponent->InitialSpeed * DeltaTime;
	const FVector Location = GetActorLocation() + Direction + Position;
	SetActorLocation(Location);

	SpiralAngle += SpiralSpeed * DeltaTime;
	if (SpiralDeviation > 0.0f && CurrentTick % 30 == 0)
	{
		--SpiralDeviation;
		CurrentTick = 0;
		UE_LOG(LogTemp, Warning, TEXT("Spiral deviation: %f"), SpiralDeviation);
	}
}

void AProjectile::FireInDirection(const FVector& Direction)
{
	DirectionNormal = Direction.GetSafeNormal();
	MovementComponent->Velocity = Direction * MovementComponent->InitialSpeed;
}

