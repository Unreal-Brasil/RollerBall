// Fill out your copyright notice in the Description page of Project Settings.


#include "Tubo.h"
#include "TheHero/TP_Rolling/TP_RollingBall.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "Components/AudioComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicsEngine/RadialForceComponent.h"


ATubo::ATubo()
{
	PrimaryActorTick.bCanEverTick = false;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_TUBO(TEXT("/Game/Geometry/Meshes/SM_Tubo"));

	USceneComponent* RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	RootComponent = RootComp;

	TuboMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TuboMeshComponent"));
	TuboMeshComponent->SetupAttachment(RootComp);

	if (SM_TUBO.Object) {
		TuboMeshComponent->SetStaticMesh(SM_TUBO.Object);
	}

	TuboMeshComponent->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));

}

// Called when the game starts or when spawned
void ATubo::BeginPlay()
{
	Super::BeginPlay();

}

