// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Explosion.generated.h"

UCLASS()
class INFINIRUNNER_API AExplosion : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExplosion();

	UPROPERTY(EditInstanceOnly, Category = "Changeables")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY()
	USceneComponent* DefaultSceneRoot;

	UPROPERTY(EditAnywhere)
	float ExplosionDuration;

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* Sphere;

	FTimerHandle MemberTimerHandle;

	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void ExplosionEnd();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
