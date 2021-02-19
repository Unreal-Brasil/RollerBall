// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tubo.generated.h"

UCLASS()
class THEHERO_API ATubo : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATubo();

private:
	class UStaticMeshComponent *TuboMeshComponent;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
};
