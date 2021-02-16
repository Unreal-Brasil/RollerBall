// Copyright Epic Games, Inc. All Rights Reserved.

#include "TP_RollingBall.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine/StaticMesh.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

ATP_RollingBall::ATP_RollingBall()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BallMesh(TEXT("/Game/Rolling/Meshes/BallMesh.BallMesh"));

	// Create mesh component for the ball
	Ball = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ball0"));
	Ball->SetStaticMesh(BallMesh.Object);
	Ball->BodyInstance.SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);
	Ball->SetSimulatePhysics(true);
	Ball->SetAngularDamping(0.1f);
	Ball->SetLinearDamping(0.1f);
	Ball->BodyInstance.MassScale = 3.5f;
	Ball->BodyInstance.MaxAngularVelocity = 800.0f;
	Ball->SetNotifyRigidBodyCollision(true);
	RootComponent = Ball;

	// Create a camera boom attached to the root (ball)
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm0"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bDoCollisionTest = false;
	SpringArm->SetUsingAbsoluteRotation(true); // Rotation of the ball should not affect rotation of boom
	SpringArm->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));
	SpringArm->TargetArmLength = 1200.f;
	SpringArm->bEnableCameraLag = false;
	SpringArm->CameraLagSpeed = 3.f;

	// Create a camera and attach to boom
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera0"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	// Set up forces
	RollTorque = 50000000.0f;
	JumpImpulse = 350000.0f;
	bCanJump = true; // Start being able to jump
}

/**
 *
 * Cria o particle effect quando o player passa pelos buracos.
 *
*/
void ATP_RollingBall::ExecuteEmitterPassRole()
{
	if (Ball != nullptr)
	{
		auto ball_loc = Ball->GetComponentLocation();
		FString particleEffectPath = "/Game/Particles/PS_PassRole";
		auto ps = Cast<UParticleSystem>(StaticLoadObject(UParticleSystem::StaticClass(), NULL, *particleEffectPath));
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ps, ball_loc, FRotator(0), true, EPSCPoolMethod::None, true);
	}
}

void ATP_RollingBall::ExecuteEmitterAtBegin()
{
	if (Ball != nullptr)
	{
		auto ball_loc = Ball->GetComponentLocation();
		FString particleEffectPath = "/Game/InfinityBladeEffects/Effects/FX_Combat_Base/Enchants/P_Enchant_Cooldowns";
		auto ps = Cast<UParticleSystem>(StaticLoadObject(UParticleSystem::StaticClass(), NULL, *particleEffectPath));
		UGameplayStatics::SpawnEmitterAttached(ps, RootComponent);
	}
}

void ATP_RollingBall::ExecuteEmitterAtDeath()
{
	if (Ball != nullptr)
	{
		auto ball_loc = Ball->GetComponentLocation();
		FString particleEffectPath = "/Game/InfinityBladeEffects/Effects/FX_Monsters/FX_Monster_Gruntling/Notifies/P_Death_backpack_expl";
		auto ps = Cast<UParticleSystem>(StaticLoadObject(UParticleSystem::StaticClass(), NULL, *particleEffectPath));
		Ball->SetVisibility(false, false);
		UGameplayStatics::SpawnEmitterAttached(ps, RootComponent);
	}
}

/**
 *
 * Ajusta o input do player.
 *
*/
void ATP_RollingBall::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	PlayerInputComponent->BindAxis("MoveRight", this, &ATP_RollingBall::MoveRight);
	PlayerInputComponent->BindAxis("MoveForward", this, &ATP_RollingBall::MoveForward);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ATP_RollingBall::Jump);
	PlayerInputComponent->BindAction("Sair", IE_Pressed, this, &ATP_RollingBall::Sair);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ATP_RollingBall::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ATP_RollingBall::TouchStopped);
}

/**
 *
 * Move o player para direita ou para a esquerda.
 *
*/
void ATP_RollingBall::MoveRight(float Val)
{
	const FVector Torque = FVector(-1.f * Val * RollTorque, 0.f, 0.f);
	Ball->AddTorqueInRadians(Torque);
}

/**
 *
 * Move o player para frente e para trás.
 *
*/
void ATP_RollingBall::MoveForward(float Val)
{
	const FVector Torque = FVector(0.f, Val * RollTorque, 0.f);
	Ball->AddTorqueInRadians(Torque);
}

/**
 * Faz o pulo da bola.
*/
void ATP_RollingBall::Jump()
{
	if (bCanJump)
	{
		const FVector Impulse = FVector(0.f, 0.f, JumpImpulse);
		Ball->AddImpulse(Impulse);
		bCanJump = false;
	}
}

void ATP_RollingBall::Sair()
{
	UGameplayStatics::OpenLevel(GetWorld(), "LMENU");
}

/**
 *
 * Notifica o Pulo.
 *
*/
void ATP_RollingBall::NotifyHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	bCanJump = true;
}

/**
 *
 * Usuário toca na tela do device.
 *
*/
void ATP_RollingBall::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	if (bCanJump)
	{
		const FVector Impulse = FVector(0.f, 0.f, JumpImpulse);
		Ball->AddImpulse(Impulse);
		bCanJump = false;
	}
}

void ATP_RollingBall::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	if (bCanJump)
	{
		const FVector Impulse = FVector(0.f, 0.f, JumpImpulse);
		Ball->AddImpulse(Impulse);
		bCanJump = false;
	}
}
