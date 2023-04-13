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
	for(int i = 0; i<5; i++)
	{

	}
}

void ALevelSpawner::SpawnPlatform(int Position)
{
	//Change FVector and FRotator to fit the correct spawn location
	AActor* ResultPawn = GetWorld()->SpawnActor<AActor>(LevelParts[Position], FVector(0,0,0), FRotator(0,0,0));
}

// Called every frame
void ALevelSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

