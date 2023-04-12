// Fill out your copyright notice in the Description page of Project Settings.


#include "RunnerCharacter.h"

ARunnerCharacter::ARunnerCharacter()
{

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
}

void ARunnerCharacter::JumpMovement(const FInputActionValue& Value)
{
	const bool CurrentValue = Value.Get<bool>();
	if (CurrentValue) {
		UE_LOG(LogTemp, Warning, TEXT("Jump"));
	}
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
