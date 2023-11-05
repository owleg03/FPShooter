// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile.generated.h"

UCLASS()
class GAMEDEV_LAB1_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	USphereComponent* CollissionComponent;

	UPROPERTY(VisibleAnywhere, Category=Movement)
	UProjectileMovementComponent* MovementComponent;

	UPROPERTY(VisibleAnywhere, Category=Projectile)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, Category=Projectile)
	float LifeSpan = 3.0f;

	UFUNCTION()
	void OnHit(
		UPrimitiveComponent* HitComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComponent,
		FVector NormalImpulse,
		const FHitResult& Hit
	);
	
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void FireInDirection(const FVector& Direction) const;

private:
	void SetupCollisionComponent();
	void SetupMovementComponent();
	void SetupMeshComponent();
};
