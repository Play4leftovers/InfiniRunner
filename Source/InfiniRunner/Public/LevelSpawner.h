// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelSpawner.generated.h"

UCLASS()
class INFINIRUNNER_API ALevelSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SpawnPlatform(int Position);

	void SpawnArrows();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AActor>> LevelParts;
	TArray<AActor*> SpawnedActor;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> Arrows;
	TArray<AActor*> SpawnedArrows;

	UPROPERTY(EditAnywhere)
	FVector TravelSpeed;

	UPROPERTY(EditAnywhere)
	FVector ArrowSpeed;

	UPROPERTY(EditAnywhere)
	float SpeedIncrease;

	UPROPERTY(EditAnywhere)
	float ArrowSpawnTimer;

	FTimerHandle MemberTimerHandle;
};
