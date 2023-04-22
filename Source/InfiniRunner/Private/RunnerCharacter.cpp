// Fill out your copyright notice in the Description page of Project Settings.


#include "RunnerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h" 
#include "GameFramework/SpringArmComponent.h"
#include "Components/PrimitiveComponent.h" 
#include "Camera/CameraComponent.h"

ARunnerCharacter::ARunnerCharacter()
{
	StaticMeshComp = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComp->SetupAttachment(RootComponent);
	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Arm"));
	CameraArm->SetupAttachment(StaticMeshComp);
	CameraArm->TargetArmLength = 200.f;
	CameraArm->AddLocalRotation(FRotator(0, -90, 0));

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(CameraArm, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;
}

void ARunnerCharacter::BeginPlay()
{
	Super::BeginPlay();

	StartingPosition = this->GetActorLocation();

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController) {
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem) {
			Subsystem->AddMappingContext(ControlMappingContext, 0);
		}
	}

	if (CameraComponent) {
		CameraComponent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	}
	SpawnedPlatform = GetWorld()->SpawnActor<AActor>(Platform, FVector(-420, -600, -404), FRotator(0, 0, 0));
	SpawnedPlatform->SetActorEnableCollision(false);
	//Spawned platform error causing character to accelerate when running on it
	//Cause: It does not move backwards, so character will not get a +- 0 on speed
	//Look into removing it completely
}

void ARunnerCharacter::JumpMovement(const FInputActionValue& Value)
{
	this->Jump();
}

void ARunnerCharacter::Damaged()
{
	Lives--;
	if (Lives == 0) {
		//Lose game
	}
	this->SetActorLocation(StartingPosition);
	StartGracePeriod();
	//If lives > 0, reset character position and create grace time
}

void ARunnerCharacter::StartGracePeriod()
{
	//Spawn platform under player to prevent falling
	SpawnedPlatform->SetActorEnableCollision(true);
	//Disable collision with normal terrain
	GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &ARunnerCharacter::StopGracePeriod, 0.1f, false, GracePeriod);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Grace Period Started"));
}

void ARunnerCharacter::StopGracePeriod()
{
	SpawnedPlatform->SetActorEnableCollision(false);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Grace Period Stopped"));
}

void ARunnerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (this->GetCharacterMovement()->IsFalling() == false) {
		this->GetCharacterMovement()->Velocity.X = XVelocity.X;
	}
}

void ARunnerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ARunnerCharacter::JumpMovement);
	}
}
