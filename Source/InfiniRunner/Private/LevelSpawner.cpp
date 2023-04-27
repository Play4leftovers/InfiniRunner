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

	GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &ALevelSpawner::SpawnArrows, ArrowSpawnTimer, true, 2.0f);
}

void ALevelSpawner::SpawnPlatform(int ArrayPosition)
{
	AActor* ResultPawn;
	FVector LastPlatformPosition = SpawnedActor.Last()->GetActorLocation();
	ResultPawn = GetWorld()->SpawnActor<AActor>(LevelParts[ArrayPosition], LastPlatformPosition + FVector(380.0, 0, 0), FRotator(0, 0, 0));
	SpawnedActor.Add(ResultPawn);
}

void ALevelSpawner::SpawnArrows()
{
	AActor* ResultPawn;
	int temp = FMath::RandRange(-256, 0);
	ResultPawn = GetWorld()->SpawnActor<AActor>(Arrows, FVector(256, -600, temp), FRotator(0, 0, 0));
	SpawnedArrows.Add(ResultPawn);
}

// Called every frame
void ALevelSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (int i = 0; i < SpawnedActor.Num(); i++) {
		AActor* TempPlatform = SpawnedActor[i];
		TempPlatform->SetActorLocation(TempPlatform->GetActorLocation() - TravelSpeed * DeltaTime);
	}
	if (SpawnedActor[0]->GetActorLocation().X < -1152.0) {
		AActor* TempPlatform = SpawnedActor[0];
		SpawnedActor.RemoveAt(0);
		TempPlatform->Destroy();
		SpawnPlatform(FMath::RandRange(0, LevelParts.Num() - 1));
	}

	if (SpawnedArrows.Num() > 0) {
		if (SpawnedArrows[0]->GetActorLocation().X < -1152.0) {
			AActor* TempArrows = SpawnedArrows[0];
			SpawnedArrows.RemoveAt(0);
			TempArrows->Destroy();
		}
		for (int i = 0; i < SpawnedArrows.Num(); i++) {
			AActor* TempArrows = SpawnedArrows[i];
			TempArrows->SetActorLocation(TempArrows->GetActorLocation() - ArrowSpeed * DeltaTime);
			if (SpawnedArrows[i]->IsHidden()) {
				TempArrows = SpawnedArrows[i];
				SpawnedArrows.RemoveAt(i);
				TempArrows->Destroy();

				if (SpawnedArrows.Num() > 0) {
					int RandomChance = FMath::RandRange(0, 100);
					if (RandomChance <= 25) {
						RandomChance = FMath::RandRange(0, SpawnedArrows.Num()-1);
						TempArrows = SpawnedArrows[RandomChance];
						SpawnedArrows.RemoveAt(RandomChance);
						TempArrows->Destroy();
					}
				}
			}
		}
	}
}

