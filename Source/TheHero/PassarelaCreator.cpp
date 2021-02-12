// Fill out your copyright notice in the Description page of Project Settings.

#include "PassarelaCreator.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "TheHeroInstance.h"
#include "MinaExplosiva.h"
#include "Components/ChildActorComponent.h"
#include "TP_Rolling/TP_RollingBall.h"

// Sets default values
APassarelaCreator::APassarelaCreator()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Counter = 0;
	AlturaPlataforma = -550.0f;
	PointToDelivery = 5;

	USceneComponent *RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	ArrowTOP = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowTOP"));
	ArrowDOWN = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowDOWN"));
	BoxDeath = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxDeath"));
	Audio = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));
	PlatformaTeto = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformaTeto"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_PASS_00_A(TEXT("/Game/Geometry/Meshes/SM_PASS_00_A"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_PASS_01_A(TEXT("/Game/Geometry/Meshes/SM_PASS_01_A"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_PASS_01_B(TEXT("/Game/Geometry/Meshes/SM_PASS_01_B"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_PASS_01_C(TEXT("/Game/Geometry/Meshes/SM_PASS_01_C"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_PASS_02_A(TEXT("/Game/Geometry/Meshes/SM_PASS_02_A"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_PASS_02_B(TEXT("/Game/Geometry/Meshes/SM_PASS_02_B"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_PASS_02_C(TEXT("/Game/Geometry/Meshes/SM_PASS_02_C"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_PASS_03_A(TEXT("/Game/Geometry/Meshes/SM_PASS_03_A"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_PASS_03_B(TEXT("/Game/Geometry/Meshes/SM_PASS_03_B"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_PASS_03_C(TEXT("/Game/Geometry/Meshes/SM_PASS_03_C"));
	static ConstructorHelpers::FObjectFinder<USoundBase> SOUND_PASS_ROLE(TEXT("/Game/Audio/confirmation-alert_Cue"));

	RootComponent = RootComp;

	ArrowTOP->SetupAttachment(RootComp);
	ArrowDOWN->SetupAttachment(RootComp);
	BoxDeath->SetupAttachment(RootComp);
	Audio->SetupAttachment(RootComp);
	PlatformaTeto->SetupAttachment(RootComp);

	BoxDeath->SetRelativeScale3D(FVector(300.0f, 300.0f, 1.0f));
	BoxDeath->SetRelativeLocation(FVector(0.0f, 0.0f, -300.0f));
	BoxDeath->SetMobility(EComponentMobility::Stationary);

	Audio->SetAutoActivate(false);

	if (SOUND_PASS_ROLE.Object != nullptr)
	{
		Audio->SetSound(SOUND_PASS_ROLE.Object);
	}
	if (SM_PASS_00_A.Object != nullptr)
	{
		Passarelas.Add(SM_PASS_00_A.Object);
	}
	if (SM_PASS_01_A.Object != nullptr)
	{
		Passarelas.Add(SM_PASS_01_A.Object);
	}
	if (SM_PASS_01_B.Object != nullptr)
	{
		Passarelas.Add(SM_PASS_01_B.Object);
	}
	if (SM_PASS_01_C.Object != nullptr)
	{
		Passarelas.Add(SM_PASS_01_C.Object);
	}
	if (SM_PASS_02_A.Object != nullptr)
	{
		Passarelas.Add(SM_PASS_02_A.Object);
	}
	if (SM_PASS_02_B.Object != nullptr)
	{
		Passarelas.Add(SM_PASS_02_B.Object);
	}
	if (SM_PASS_02_C.Object != nullptr)
	{
		Passarelas.Add(SM_PASS_02_C.Object);
	}
	if (SM_PASS_03_A.Object != nullptr)
	{
		Passarelas.Add(SM_PASS_03_A.Object);
	}
	if (SM_PASS_03_B.Object != nullptr)
	{
		Passarelas.Add(SM_PASS_03_B.Object);
	}
	if (SM_PASS_03_C.Object != nullptr)
	{
		Passarelas.Add(SM_PASS_03_C.Object);
	}

	FVector VecMeshLoc;
	VecMeshLoc.Z = AlturaPlataforma * 0;

	PlatformaTeto->SetRelativeLocation(VecMeshLoc);
	PlatformaTeto->SetStaticMesh(Passarelas[0]);
	PlatformaTeto->SetRelativeScale3D(FVector(3.0f, 1.0f, 1.0f));
}

// Called when the game starts or when spawned
void APassarelaCreator::BeginPlay()
{
	Super::BeginPlay();

	for (size_t i = 0; i < 10; i++)
	{
		CriarPlatform();
	}

	BoxDeath->OnComponentBeginOverlap.AddDynamic(this, &APassarelaCreator::BoxDeathOverlapBegin);
	//GetWorld()->GetTimerManager().SetTimer(LoadPlatformTimerHandle, this, &APassarelaCreator::CriarPlatform, 3, true);
	GetWorld()->GetTimerManager().SetTimer(DestroyPlatformTimerHandle, this, &APassarelaCreator::DestruirPlatform, 3, true);
	GetWorld()->GetTimerManager().SetTimer(DestroyMinasTimerHandle, this, &APassarelaCreator::DestruirMinasNaoUsadas, 3, true);
}

void APassarelaCreator::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}

/**
 * Este método é bom. Ele cria plataformas.
*/
void APassarelaCreator::CriarPlatform()
{
	Counter++;

	FVector VecMeshLoc;
	VecMeshLoc.Z = AlturaPlataforma * Counter;

	UStaticMeshComponent *SMComp = NewObject<UStaticMeshComponent>(this);
	SMComp->SetupAttachment(RootComponent);
	SMComp->SetRelativeLocation(VecMeshLoc);
	SMComp->SetRelativeScale3D(FVector(3.0f, 1.0f, 1.0f));

	auto SmToAdd = Passarelas[FMath::RandRange(1, Passarelas.Num() - 1)];

	SMComp->SetStaticMesh(SmToAdd);
	SMComp->RegisterComponent();

	ArrowDOWN->SetRelativeLocation(VecMeshLoc);
	BoxDeath->SetRelativeLocation(VecMeshLoc);

	UBoxComponent *BoxCompPassRole = NewObject<UBoxComponent>(this);
	BoxCompPassRole->SetupAttachment(RootComponent);
	BoxCompPassRole->SetRelativeLocation(VecMeshLoc);
	BoxCompPassRole->SetGenerateOverlapEvents(true);
	BoxCompPassRole->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	BoxCompPassRole->SetRelativeScale3D(FVector(4.0f, 42.0f, 2.0f));
	BoxCompPassRole->OnComponentBeginOverlap.AddDynamic(this, &APassarelaCreator::BoxPassRoleOverlapBegin);
	BoxCompPassRole->RegisterComponent();

	CriarMina(VecMeshLoc);
}

/**
 * Belo método para destruir as plataformas que estão acima do player.
*/
void APassarelaCreator::DestruirPlatform()
{
	TArray<UStaticMeshComponent *> outComp;
	GetComponents<UStaticMeshComponent>(outComp);

	auto MyPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	for (auto &&i : outComp)
	{
		FVector mesh_comp_loc = i->GetComponentLocation();
		FVector pawn_loc = MyPawn->GetActorLocation();

		if (mesh_comp_loc.Z > pawn_loc.Z)
		{
			i->DestroyComponent();
		}
	}
}

void APassarelaCreator::DestruirMinasNaoUsadas()
{
	TArray<UChildActorComponent *> outComp;
	GetComponents<UChildActorComponent>(outComp);

	auto MyPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	for (auto &&i : outComp)
	{
		FVector mesh_comp_loc = i->GetComponentLocation();
		FVector pawn_loc = MyPawn->GetActorLocation();

		if (mesh_comp_loc.Z > pawn_loc.Z)
		{
			i->DestroyComponent();
		}
	}
}

void APassarelaCreator::CriarMina(FVector loc)
{

	int32 NumMinas = FMath::RandRange(0, 3);

	for (int32 i = 0; i < NumMinas; i++)
	{
		UChildActorComponent *MinaToSpawn = NewObject<UChildActorComponent>(this);
		MinaToSpawn->SetupAttachment(RootComponent);
		// XUXU CAPETA.
		FVector InnerPosition(FMath::RandRange(-80, 80), FMath::RandRange(-1300, 1300), loc.Z + 150);
		MinaToSpawn->SetRelativeLocation(InnerPosition);
		MinaToSpawn->SetChildActorClass(AMinaExplosiva::StaticClass());
		MinaToSpawn->RegisterComponent();
	}
}

/**
 * Método maroto chamado a cada frame.
*/
void APassarelaCreator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APassarelaCreator::BoxDeathOverlapBegin(class UPrimitiveComponent *OverlappedComp, class AActor *Other, class UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	auto Player = Cast<ATP_RollingBall>(Other);
	if (Player != nullptr)
	{
		OnPlayerDiedNow.Broadcast();
		UE_LOG(LogTemp, Warning, TEXT("BoxDeathOverlapBegin"));
	}
}

void APassarelaCreator::BoxPassRoleOverlapBegin(class UPrimitiveComponent *OverlappedComp, class AActor *Other, class UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	auto Player = Cast<ATP_RollingBall>(Other);
	if (Player != nullptr)
	{
		OverlappedComp->DestroyComponent();

		auto GI = GetGameInstance();
		if (GI != nullptr)
		{
			auto GameInst = Cast<UTheHeroInstance>(GI);
			if (GameInst)
			{
				OnPlayerGotPoint.Broadcast(PointToDelivery);
				GameInst->UpdatePlayerScore(PointToDelivery);
				Player->ExecuteEmitterPassRole();
				Audio->Play();
				CriarPlatform();
			}
		}
	}
}