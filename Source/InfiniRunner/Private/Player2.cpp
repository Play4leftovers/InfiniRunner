// Fill out your copyright notice in the Description page of Project Settings.


#include "Player2.h"
#include "GameFramework/CharacterMovementComponent.h" 

APlayer2::APlayer2()
{
	StaticMeshComp = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComp->SetupAttachment(RootComponent);
}

void APlayer2::BeginPlay()
{
	Super::BeginPlay();
	StartingPosition = this->GetActorLocation();
}

void APlayer2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (this->GetCharacterMovement()->IsFalling() == false) {
		this->GetCharacterMovement()->Velocity.X = XVelocity.X + MovementModifier;
		MovementModifier = 0;
	}
}

void APlayer2::JumpMovement()
{
	this->Jump();
}

void APlayer2::LeftMovement()
{
	MovementModifier = -SpeedIncrease;
}

void APlayer2::RightMovement()
{
	MovementModifier = SpeedIncrease;
}

void APlayer2::SetPlayer1(ARunnerCharacter* Player1)
{
	PlayerOne = Player1;
}

void APlayer2::Damaged()
{
	if (!CanBeDamaged) {
		return;
	}
	this->SetActorLocation(StartingPosition);
	PlayerOne->Damaged();
}
