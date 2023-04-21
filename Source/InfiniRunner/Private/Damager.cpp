// Fill out your copyright notice in the Description page of Project Settings.


#include "Damager.h"
#include "RunnerCharacter.h"

// Sets default values
ADamager::ADamager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(FName("DefaultSceneRoot"));
	SetRootComponent(DefaultSceneRoot);
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMesh"));
	StaticMesh->SetupAttachment(DefaultSceneRoot);
	Box = CreateDefaultSubobject<UBoxComponent>(FName("Box"));
	Box->SetupAttachment(DefaultSceneRoot);
}

// Called when the game starts or when spawned
void ADamager::BeginPlay()
{
	Super::BeginPlay();
	Box->OnComponentBeginOverlap.AddDynamic(this, &ADamager::OverlapBegin);
	Box->OnComponentEndOverlap.AddDynamic(this, &ADamager::OverlapEnd);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("I exist now"));
}

void ADamager::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ARunnerCharacter* TempChar = Cast<ARunnerCharacter>(OtherActor);
	if (TempChar) {
		TempChar->Damaged();
	}
}

void ADamager::OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

// Called every frame
void ADamager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

