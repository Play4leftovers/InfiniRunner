// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "RunnerCharacter.h"
#include "Player2.generated.h"

/**
 * 
 */
UCLASS()
class INFINIRUNNER_API APlayer2 : public APaperCharacter
{
	GENERATED_BODY()
public:
	APlayer2();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere)
	float SpeedIncrease;

	UPROPERTY(EditAnywhere)
	ARunnerCharacter* PlayerOne;

	UPROPERTY(EditAnywhere)
	FVector XVelocity;

	UPROPERTY(EditAnywhere)
	FVector StartingPosition;

	float MovementModifier;

public:
	virtual void Tick(float DeltaTime) override;

	void JumpMovement();
	void LeftMovement();
	void RightMovement();
	void SetPlayer1(ARunnerCharacter* Player1);
	void Damaged();
};
