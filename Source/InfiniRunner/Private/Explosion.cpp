// Fill out your copyright notice in the Description page of Project Settings.


#include "Explosion.h"
#include "RunnerCharacter.h"
#include "Components/SphereComponent.h" 
// Sets default values
AExplosion::AExplosion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(FName("DefaultSceneRoot"));
	SetRootComponent(DefaultSceneRoot);
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMesh"));
	StaticMesh->SetupAttachment(DefaultSceneRoot);
	Sphere = CreateDefaultSubobject<USphereComponent>(FName("Sphere"));
	Sphere->SetupAttachment(DefaultSceneRoot);
}

// Called when the game starts or when spawned
void AExplosion::BeginPlay()
{
	Super::BeginPlay();
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AExplosion::OverlapBegin);
	GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &AExplosion::ExplosionEnd, 0.1f, false, ExplosionDuration);
}

void AExplosion::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ARunnerCharacter* TempChar = Cast<ARunnerCharacter>(OtherActor);
	if (TempChar) {
		TempChar->Damaged();
	}
}

void AExplosion::ExplosionEnd()
{
	this->Destroy();
}

