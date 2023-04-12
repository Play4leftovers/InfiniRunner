// Fill out your copyright notice in the Description page of Project Settings.


#include "RunnerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

ARunnerCharacter::ARunnerCharacter()
{
	StaticMeshComp = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComp->SetupAttachment(RootComponent);
	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Arm"));
	CameraArm->SetupAttachment(StaticMeshComp);
	CameraArm->TargetArmLength = 100.f;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(CameraArm, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;
}

void ARunnerCharacter::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController) {
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem) {
			Subsystem->AddMappingContext(JumpMappingContext, 0);
		}
	}

	/*if (CameraComponent) {
		CameraComponent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	}*/
}

void ARunnerCharacter::JumpMovement(const FInputActionValue& Value)
{
	this->Jump();
}

void ARunnerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARunnerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ARunnerCharacter::JumpMovement);
	}
}
