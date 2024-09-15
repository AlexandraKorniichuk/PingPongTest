// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"

#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ABall::ABall()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ball"));
	Mesh->SetMobility(EComponentMobility::Movable);
	SetRootComponent(Mesh);
}

void ABall::BeginPlay()
{
	Super::BeginPlay();

	MovementVector = UKismetMathLibrary::RandomUnitVector();
    MovementVector.Z = 0.0f;
	MovementVector.Normalize();
	
	StartLocation = GetActorLocation();
}

void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FVector TargetVelocity = MovementVector * MoveSpeed * FVector(1.0f, 1.0f, 0.0f);
	const FVector ToInterp = TargetVelocity + GetActorLocation();
	const FVector NewLocation = FMath::VInterpTo(GetActorLocation(), ToInterp, DeltaTime, 15.0f);
	FHitResult HitResult;
	Mesh->SetWorldLocation(NewLocation, true, &HitResult);

	if (GetLocalRole() == ROLE_Authority && HitResult.bBlockingHit)
	{
		const FVector NewMovementVector = FMath::GetReflectionVector(
			(HitResult.TraceEnd - HitResult.TraceStart).GetSafeNormal(),
			HitResult.ImpactNormal);

		MovementVector = NewMovementVector;
	}
}

void ABall::ResetLocation()
{
	SetActorLocation(StartLocation);
}

void ABall::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABall, MovementVector);
}
