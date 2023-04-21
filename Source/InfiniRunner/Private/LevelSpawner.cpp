// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelSpawner.h"
#include "Engine/World.h" 

// Sets default values
ALevelSpawner::ALevelSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALevelSpawner::BeginPlay()
{
	Super::BeginPlay();

	AActor* ResultPawn;
	ResultPawn = GetWorld()->SpawnActor<AActor>(LevelParts[0], FVector(-768, -600, 0), FRotator(0, 0, 0));
	SpawnedActor.Add(ResultPawn);

	for(int i = 0; i<3; i++)
	{
		SpawnPlatform(0);
	}
}

void ALevelSpawner::SpawnPlatform(int ArrayPosition)
{
	AActor* ResultPawn;
	FVector LastPlatformPosition = SpawnedActor.Last()->GetActorLocation();
	ResultPawn = GetWorld()->SpawnActor<AActor>(LevelParts[ArrayPosition], LastPlatformPosition + FVector(380.0, 0, 0), FRotator(0, 0, 0));
	SpawnedActor.Add(ResultPawn);
}

// Called every frame
void ALevelSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//TravelSpeed.X -= SpeedIncrease;
	for (int i = 0; i < SpawnedActor.Num(); i++) {
		AActor* temp = SpawnedActor[i];
		temp->SetActorLocation(temp->GetActorLocation() - TravelSpeed * DeltaTime);
	}

	if (SpawnedActor[0]->GetActorLocation().X < -1152.0) {
		AActor* temp = SpawnedActor[0];
		SpawnedActor.RemoveAt(0);
		temp->Destroy();
		SpawnPlatform(FMath::RandRange(0, LevelParts.Num() - 1));
	}
}

