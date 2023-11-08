// ReSharper disable CppUENonExistentInputAxis
// ReSharper disable CppUENonExistentInputAction

#include "MainCharacter.h"

#include "PhysXInterfaceWrapperCore.h"
#include "GameFramework/PawnMovementComponent.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
  // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

  // Enable crouching
  UPawnMovementComponent* MovementComponent = ACharacter::GetMovementComponent();
  if (MovementComponent)
  {
     MovementComponent->GetNavAgentPropertiesRef().bCanCrouch = true;
  }

  SetupCameraComponent();
  SetupGunSkeletalMeshComponent();
}

void AMainCharacter::SetupCameraComponent()
{
  // Create and attach a camera component
  CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
  check(CameraComponent != nullptr);
  CameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));

  // Position the camera component
  CameraComponent->SetRelativeLocation(FVector(10.0f, 5.0f, BaseEyeHeight + 5.0f));

  // Enable camera control
  CameraComponent->bUsePawnControlRotation = true;
  
  GetMesh()->SetupAttachment(CameraComponent);
}

void AMainCharacter::SetupGunSkeletalMeshComponent()
{
  // Create and attach a gun skeletal mesh component
  GunSkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunSkeletalMeshComponent"));
  GunSkeletalMeshComponent->bCastDynamicShadow = false;
  GunSkeletalMeshComponent->CastShadow = false;
  GunSkeletalMeshComponent->SetupAttachment(CameraComponent);
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
  Super::BeginPlay();

  check(GEngine != nullptr);

  // Attach gun skeletal mesh to the main mesh
  GunSkeletalMeshComponent->AttachToComponent(
      GetMesh(),
      FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true),
      TEXT("WeaponPoint")
  );
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
  Super::SetupPlayerInputComponent(PlayerInputComponent);

  // Bind axes
  PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
  PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);
  PlayerInputComponent->BindAxis("Turn", this, &AMainCharacter::AddControllerYawInput);
  PlayerInputComponent->BindAxis("LookUp", this, &AMainCharacter::AddControllerPitchInput);

  // Bind actions
  PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMainCharacter::StartJump);
  PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMainCharacter::EndJump);
  PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AMainCharacter::StartCrouch);
  PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AMainCharacter::EndCrouch);
  PlayerInputComponent->BindAction("TurnAround", IE_Pressed, this, &AMainCharacter::TurnAround);
  PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMainCharacter::Fire);
}

// Handles forward/backward movement
void AMainCharacter::MoveForward(float Value)
{
  const FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
  AddMovementInput(Direction, Value);
}

// Handles right/left movement
void AMainCharacter::MoveRight(float Value)
{
  const FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
  AddMovementInput(Direction, Value);
}

// Handles jump start
void AMainCharacter::StartJump()
{
  bPressedJump = true;
}

// Handles jump end
void AMainCharacter::EndJump()
{
  bPressedJump = false;
}

// Handles crouch start
void AMainCharacter::StartCrouch()
{
  Crouch();
}

// Handles crouch end
void AMainCharacter::EndCrouch()
{
  UnCrouch();
}

// Handles turning 180 degrees
void AMainCharacter::TurnAround()
{
  AddControllerYawInput(360.f);
}

// Handles firing a weapon
void AMainCharacter::Fire()
{
  if (!ProjectileClass)
  {
    return;
  } 
  
  FVector CameraLocation;
  FRotator CameraRotation;
  GetActorEyesViewPoint(CameraLocation, CameraRotation);

  const FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);
  const FRotator MuzzleRotation = CameraRotation;
  FActorSpawnParameters SpawnParameters;
  SpawnParameters.Owner = this;
  SpawnParameters.Instigator = GetInstigator();
  SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

  AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
      ProjectileClass,
      MuzzleLocation,
      MuzzleRotation,
      SpawnParameters
  );
  if (Projectile)
  {
    const FVector LaunchDirection = MuzzleRotation.Vector();
    Projectile->FireInDirection(LaunchDirection);
  }
}
