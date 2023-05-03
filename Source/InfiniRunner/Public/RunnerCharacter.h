// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "RunnerCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
class UCameraComponent;
class USpringArmComponent;
class APlayer2;

/**
 * 
 */
UCLASS()
class INFINIRUNNER_API ARunnerCharacter : public APaperCharacter
{
	GENERATED_BODY()
	
public:
	ARunnerCharacter();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* ControlMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		UInputAction* LeftAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		UInputAction* RightAction;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		UInputAction* JumpAction2;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		UInputAction* LeftAction2;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		UInputAction* RightAction2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
	USpringArmComponent* CameraArm;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AActor> Platform;
	AActor* SpawnedPlatform;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> SecondPlayerActor;
	APlayer2* Player2;

	FTimerHandle MemberTimerHandle;

	UPROPERTY(EditAnywhere)
	float SpeedIncrease;

	UPROPERTY(EditAnywhere)
	float GracePeriod;

	UPROPERTY(EditAnywhere)
	FVector XVelocity;

	UPROPERTY(EditAnywhere)
	FVector StartingPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Lives;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Score;
	FTimerHandle ScoreTimerHandle;

	bool CanBeDamaged;

	float MovementModifier;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void JumpMovement(const FInputActionValue& Value);
	void LeftMovement(const FInputActionValue& Value);
	void RightMovement(const FInputActionValue& Value);
	void JumpMovementPlayer2(const FInputActionValue& Value);
	void LeftMovementPlayer2(const FInputActionValue& Value);
	void RightMovementPlayer2(const FInputActionValue& Value);

	UFUNCTION()
	void CreatePlayer2();

	void Damaged();

	UFUNCTION()
	void GameLost();

	void StartGracePeriod();
	void StopGracePeriod();

	void ScorePoint();
};
