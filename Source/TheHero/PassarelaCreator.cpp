#include "PassarelaCreator.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "TheHeroInstance.h"
#include "PhysicsEngine/BoxElem.h"
#include "PhysicsEngine/BodySetup.h"
#include "MinaExplosiva.h"
#include "Engine/StaticMesh.h"
#include "Components/ChildActorComponent.h"
#include "TP_Rolling/TP_RollingBall.h"
#include "DrawDebugHelpers.h"
#include "Tubo.h"

// Sets default values
APassarelaCreator::APassarelaCreator()
{
	Counter = 0;
	AlturaPlataforma = -550.0f;
	PointToDelivery = 5;
	PosicaoCockpit = FVector(0, 0, 0);
	USceneComponent* RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	ArrowTOP = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowTOP"));
	ArrowDOWN = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowDOWN"));
	BoxDeath = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxDeath"));
	Audio = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));
	PlatformaTeto = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformaTeto"));
	CockpitFundo = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CockpitFundo"));


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
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_COCKPIT_FUNDO(TEXT("/Game/Geometry/Meshes/SM_Cockpit"));
	///
	static ConstructorHelpers::FObjectFinder<USoundBase> SOUND_PASS_ROLE(TEXT("/Game/Audio/confirmation-alert_Cue"));

	RootComponent = RootComp;

	ArrowTOP->SetupAttachment(RootComp);
	ArrowDOWN->SetupAttachment(RootComp);
	BoxDeath->SetupAttachment(RootComp);
	Audio->SetupAttachment(RootComp);
	PlatformaTeto->SetupAttachment(RootComp);
	CockpitFundo->SetupAttachment(RootComp);

	BoxDeath->SetRelativeScale3D(FVector(300.0f, 300.0f, 1.0f));
	BoxDeath->SetRelativeLocation(FVector(0.0f, 0.0f, -300.0f));
	BoxDeath->SetMobility(EComponentMobility::Stationary);

	Audio->SetAutoActivate(false);

	if (SM_COCKPIT_FUNDO.Object != nullptr) {
		CockpitFundo->SetStaticMesh(SM_COCKPIT_FUNDO.Object);
	}
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

	PosicaoCockpit = CockpitFundo->GetRelativeLocation();
	PosicaoCockpit.Y = 1368;
	PosicaoCockpit.Z = 2500;
	CockpitFundo->SetMobility(EComponentMobility::Movable);
	CockpitFundo->SetRelativeLocation(PosicaoCockpit);
}

// Called when the game starts or when spawned
void APassarelaCreator::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < 5; i++)
	{
		CriarPlatform();
	}

	BoxDeath->OnComponentBeginOverlap.AddDynamic(this, &APassarelaCreator::BoxDeathOverlapBegin);
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

	UStaticMeshComponent* SMComp = NewObject<UStaticMeshComponent>(this);
	SMComp->SetupAttachment(RootComponent);
	SMComp->SetRelativeLocation(VecMeshLoc);
	SMComp->SetRelativeScale3D(FVector(3.0f, 1.0f, 1.0f));

	auto SmToAdd = Passarelas[FMath::RandRange(1, Passarelas.Num() - 1)];

	SMComp->SetStaticMesh(SmToAdd);
	SMComp->RegisterComponent();

	TArray<FKBoxElem> box_elements = SMComp->GetBodySetup()->AggGeom.BoxElems;

	ArrowDOWN->SetRelativeLocation(VecMeshLoc);
	BoxDeath->SetRelativeLocation(VecMeshLoc);

	CockpitFundo->SetRelativeScale3D(FVector(1, 1, 3));
	PosicaoCockpit = CockpitFundo->GetRelativeLocation();
	PosicaoCockpit.Z = PosicaoCockpit.Z - 400.0f;
	CockpitFundo->SetRelativeLocation(PosicaoCockpit);

	UBoxComponent* BoxCompPassRole = NewObject<UBoxComponent>(this);
	BoxCompPassRole->SetupAttachment(RootComponent);
	BoxCompPassRole->SetRelativeLocation(VecMeshLoc);
	BoxCompPassRole->SetGenerateOverlapEvents(true);
	BoxCompPassRole->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	BoxCompPassRole->SetRelativeScale3D(FVector(4.0f, 42.0f, 2.0f));
	BoxCompPassRole->OnComponentBeginOverlap.AddDynamic(this, &APassarelaCreator::BoxPassRoleOverlapBegin);
	BoxCompPassRole->RegisterComponent();

	CriarMina(VecMeshLoc, box_elements);
}


/**
 * Belo método para destruir as plataformas que estão acima do player.
*/
void APassarelaCreator::DestruirPlatform()
{
	TArray<UStaticMeshComponent*> outComp;
	GetComponents<UStaticMeshComponent>(outComp);

	auto MyPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	for (auto&& i : outComp)
	{
		const FString ObjName = i->GetName();
		if (!ObjName.Equals("CockpitFundo")) {
			FVector mesh_comp_loc = i->GetComponentLocation();
			FVector pawn_loc = MyPawn->GetActorLocation();

			if (mesh_comp_loc.Z > pawn_loc.Z)
			{
				i->DestroyComponent();
			}
		}
	}
}

void APassarelaCreator::DestruirMinasNaoUsadas()
{
	TArray<UChildActorComponent*> outComp;
	GetComponents<UChildActorComponent>(outComp);

	auto MyPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	for (auto&& i : outComp)
	{
		FVector mesh_comp_loc = i->GetComponentLocation();
		FVector pawn_loc = MyPawn->GetActorLocation();

		if (mesh_comp_loc.Z > pawn_loc.Z)
		{
			i->DestroyComponent();
		}
	}
}

/**
* QUE FUNÇÃO DOS INFERNOS PARA CONSTRUIR.
*/
void APassarelaCreator::CriarMina(FVector loc, TArray<FKBoxElem> box_coll)
{
	int32 NumMinas = FMath::RandRange(0, 2);
	for (auto&& i : box_coll)
	{
		FVector CENTRO = i.Center;
		FVector TAMANHO = FVector(i.X, i.Y, i.Z);
		FVector MEIO = TAMANHO / 2.0f;
		FVector ESQUERDA = CENTRO - MEIO;
		FVector DIREITA = CENTRO + MEIO;

		if (TAMANHO.Y >= 350.0f) {

			for (int32 x = 0; x < NumMinas; x++)
			{
				UChildActorComponent* MinaToSpawn = NewObject<UChildActorComponent>(this);
				MinaToSpawn->SetupAttachment(RootComponent);
				FVector InnerPosition(FMath::RandRange(ESQUERDA.X, DIREITA.X), FMath::RandRange(ESQUERDA.Y, DIREITA.Y), loc.Z + DIREITA.Z);
				MinaToSpawn->SetRelativeLocation(InnerPosition);
				MinaToSpawn->SetChildActorClass(AMinaExplosiva::StaticClass());
				MinaToSpawn->RegisterComponent();
			}
		}

		if (box_coll.Num() > 1) {
			CriarTubo(loc.X, DIREITA.Y+110, loc.Z-25);
		}
	}
}

void APassarelaCreator::CriarTubo(float X, float Y, float Z)
{

	UChildActorComponent* TuboToSpawn = NewObject<UChildActorComponent>(this);
	TuboToSpawn->SetupAttachment(RootComponent);
	FVector InnerPosition(X, Y, Z);
	TuboToSpawn->SetRelativeLocation(InnerPosition);
	TuboToSpawn->SetRelativeScale3D(FVector(1.1f, 1.1f, 2.5f));
	TuboToSpawn->SetChildActorClass(ATubo::StaticClass());
	TuboToSpawn->RegisterComponent();
}



void APassarelaCreator::BoxDeathOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* Other, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto Player = Cast<ATP_RollingBall>(Other);
	if (Player != nullptr)
	{
		OnPlayerDiedNow.Broadcast();
	}
}

void APassarelaCreator::BoxPassRoleOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* Other, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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