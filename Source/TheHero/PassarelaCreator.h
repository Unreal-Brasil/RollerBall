// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PassarelaCreator.generated.h"

UCLASS()
class THEHERO_API APassarelaCreator : public AActor
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerDied);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerGotPoint, int, ponto);

public:
	// Sets default values for this actor's properties
	APassarelaCreator();
	virtual void Tick(float DeltaTime) override;

	TArray<class UStaticMesh *> Passarelas;

	UPROPERTY(BlueprintAssignable)
	FPlayerDied OnPlayerDied;

	UPROPERTY(BlueprintAssignable)
	FPlayerGotPoint OnPlayerGotPoint;

private:
	FTimerHandle LoadPlatformTimerHandle;
	FTimerHandle DestroyPlatformTimerHandle;
	int Counter;
	float AlturaPlataforma;
	int PointToDelivery;

	class UArrowComponent *ArrowTOP;
	class UArrowComponent *ArrowDOWN;
	class UBoxComponent *BoxDeath;
	class UAudioComponent *Audio;
	class UStaticMeshComponent *PlatformaTeto;

	UFUNCTION()
	void BoxDeathOverlapBegin(class UPrimitiveComponent *OverlappedComp, class AActor *Other, class UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
	UFUNCTION()
	void BoxPassRoleOverlapBegin(class UPrimitiveComponent *OverlappedComp, class AActor *Other, class UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION()
	void CriarPlatform();

	UFUNCTION()
	void DestruirPlatform();
};
