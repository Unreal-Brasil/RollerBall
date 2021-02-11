// Fill out your copyright notice in the Description page of Project Settings.

#include "MinaExplosiva.h"

#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "Components/AudioComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMinaExplosiva::AMinaExplosiva()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_MINE(TEXT("/Game/Geometry/Meshes/MaterialSphere"));

	USceneComponent *RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	MineMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MineMeshComponent"));
	RootComponent = RootComp;

	MineMeshComponent->AttachToComponent(RootComp, FAttachmentTransformRules::KeepRelativeTransform);
	MineMeshComponent->SetStaticMesh(SM_MINE.Object);
	MineMeshComponent->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
}

// Called when the game starts or when spawned
void AMinaExplosiva::BeginPlay()
{
	Super::BeginPlay();
}
