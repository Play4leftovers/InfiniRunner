// Fill out your copyright notice in the Description page of Project Settings.


#include "RunnerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h" 
#include "GameFramework/SpringArmComponent.h"
#include "Components/PrimitiveComponent.h" 
#include "Player2.h"
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
	CreatePlayer2();
	SpawnedPlatform = GetWorld()->SpawnActor<AActor>(Platform, FVector(-420, -600, -404), FRotator(0, 0, 0));
	SpawnedPlatform->SetActorEnableCollision(false);
	CanBeDamaged = true;
	//Spawned platform error causing character to accelerate when running on it
	//Cause: It does not move backwards, so character will not get a +- 0 on speed
	//Look into removing it completely
}

void ARunnerCharacter::JumpMovement(const FInputActionValue& Value)
{
	this->Jump();
}

void ARunnerCharacter::LeftMovement(const FInputActionValue& Value)
{
	MovementModifier = -SpeedIncrease;
}

void ARunnerCharacter::RightMovement(const FInputActionValue& Value)
{
	MovementModifier = SpeedIncrease;
}

void ARunnerCharacter::JumpMovementPlayer2(const FInputActionValue& Value)
{
	Player2->JumpMovement();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Player Two Jump Called"));
}

void ARunnerCharacter::LeftMovementPlayer2(const FInputActionValue& Value)
{
	Player2->LeftMovement();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Player Two Move Left Called"));
}

void ARunnerCharacter::RightMovementPlayer2(const FInputActionValue& Value)
{
	Player2->RightMovement();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Player Two Move Right Called"));
}

void ARunnerCharacter::CreatePlayer2()
{
	Player2 = GetWorld()->SpawnActor<APlayer2>(SecondPlayerActor, StartingPosition + FVector(128,0,0), FRotator(0, 0, 0));
	Player2->SetPlayer1(this);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Ran CreatePlayer2"));
}

void ARunnerCharacter::Damaged()
{
	if (!CanBeDamaged) {
		return;
	}
	
	Lives--;
	if (Lives == 0) {
		//Lose game
	}
	this->SetActorLocation(StartingPosition);
	StartGracePeriod();
}

void ARunnerCharacter::StartGracePeriod()
{
	SpawnedPlatform->SetActorEnableCollision(true);
	CanBeDamaged = false;
	GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &ARunnerCharacter::StopGracePeriod, 0.1f, false, GracePeriod);
}

void ARunnerCharacter::StopGracePeriod()
{
	CanBeDamaged = true;
	SpawnedPlatform->SetActorEnableCollision(false);
}

void ARunnerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (this->GetCharacterMovement()->IsFalling() == false) {
		this->GetCharacterMovement()->Velocity.X = XVelocity.X + MovementModifier;
		MovementModifier = 0;
	}
}

void ARunnerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ARunnerCharacter::JumpMovement);
		EnhancedInputComponent->BindAction(LeftAction, ETriggerEvent::Triggered, this, &ARunnerCharacter::LeftMovement);
		EnhancedInputComponent->BindAction(RightAction, ETriggerEvent::Triggered, this, &ARunnerCharacter::RightMovement);


		EnhancedInputComponent->BindAction(JumpAction2, ETriggerEvent::Started, this, &ARunnerCharacter::JumpMovementPlayer2);
		EnhancedInputComponent->BindAction(LeftAction2, ETriggerEvent::Triggered, this, &ARunnerCharacter::LeftMovementPlayer2);
		EnhancedInputComponent->BindAction(RightAction2, ETriggerEvent::Triggered, this, &ARunnerCharacter::RightMovementPlayer2);
	}
}
