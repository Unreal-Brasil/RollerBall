// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MinaExplosiva.generated.h"

UCLASS()
class THEHERO_API AMinaExplosiva : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMinaExplosiva();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	class UStaticMeshComponent *MineMeshComponent;
	class URadialForceComponent *ForcaExplosaoComponent;

	bool bExploded;

	UFUNCTION()
	void MinaOverlapBegin(class UPrimitiveComponent *OverlappedComp, class AActor *Other, class UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
};
