// Fill out your copyright notice in the Description page of Project Settings.

#include "MinaExplosiva.h"
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

// Sets default values
AMinaExplosiva::AMinaExplosiva()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_MINE(TEXT("/Game/Geometry/Meshes/MaterialSphere"));
	static ConstructorHelpers::FObjectFinder<USoundBase> SOUND_EXPLODE(TEXT("/Game/Audio/phasingbeam02_Cue"));

	USceneComponent* RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	Audio = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));

	RootComponent = RootComp;

	MineMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MineMeshComponent"));
	MineMeshComponent->SetupAttachment(RootComp);

	if (SM_MINE.Object != nullptr) {
		MineMeshComponent->SetStaticMesh(SM_MINE.Object);
	}

	MineMeshComponent->SetRelativeScale3D(FVector(1.5f, 1.5f, 1.5f));

	ForcaExplosaoComponent = CreateDefaultSubobject<URadialForceComponent>(TEXT("ForcaExplosaoComponent"));
	ForcaExplosaoComponent->SetupAttachment(MineMeshComponent);
	ForcaExplosaoComponent->bImpulseVelChange = true;
	ForcaExplosaoComponent->bAutoActivate = false;
	ForcaExplosaoComponent->bIgnoreOwningActor = true;
	ForcaExplosaoComponent->Radius = 1000;

	Audio->SetupAttachment(RootComp);
	Audio->SetAutoActivate(false);

	if (SOUND_EXPLODE.Object != nullptr)
	{
		Audio->SetSound(SOUND_EXPLODE.Object);
	}
}

// Called when the game starts or when spawned
void AMinaExplosiva::BeginPlay()
{
	Super::BeginPlay();

	MineMeshComponent->SetGenerateOverlapEvents(true);
	MineMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	MineMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AMinaExplosiva::MinaOverlapBegin);
}

void AMinaExplosiva::MinaOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* Other, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("MinaOverlapBegin"));
	if (bExploded)
		return;

	auto player = Cast<ATP_RollingBall>(Other);
	if (player != nullptr)
	{
		bExploded = true;
		MineMeshComponent->SetVisibility(false, false);
		FString particleEffectPath = "/Game/StarterContent/Particles/P_Explosion";
		auto _loc = OverlappedComp->GetComponentLocation();
		auto ps = Cast<UParticleSystem>(StaticLoadObject(UParticleSystem::StaticClass(), NULL, *particleEffectPath));
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ps, _loc, FRotator(0), true, EPSCPoolMethod::None, true);
		ForcaExplosaoComponent->Activate();
		ForcaExplosaoComponent->FireImpulse();
		Audio->Play();
		UE_LOG(LogTemp, Warning, TEXT("Audio->Play();"));
		this->SetLifeSpan(3);
	}
}
