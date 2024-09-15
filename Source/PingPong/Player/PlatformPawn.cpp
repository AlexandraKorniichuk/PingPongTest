// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformPawn.h"
#include "Net/UnrealNetwork.h"

APlatformPawn::APlatformPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform"));
	PlatformMesh->SetMobility(EComponentMobility::Movable);
	SetRootComponent(PlatformMesh);
}

void APlatformPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveX", this, &APlatformPawn::Move);
}

void APlatformPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const float MovementInputValue = IsLocallyControlled() ? LastXAxisInputValue : DesiredXAcceleration;
	const FVector TargetVelocity = MovementInputValue * GetActorRightVector() * MoveSpeed;
	const FVector ToInterp = TargetVelocity + GetActorLocation();
	const FVector NewLocation = FMath::VInterpTo(GetActorLocation(), ToInterp, DeltaTime, 0.5f);

	SetActorLocation(NewLocation, true);
}

void APlatformPawn::Move(float AxisValue)
{
	if (FMath::IsNearlyEqual(LastXAxisInputValue, AxisValue, 0.1f))
		return;
	
	LastXAxisInputValue = AxisValue;
	MovePlatformServer(LastXAxisInputValue);
}

void APlatformPawn::MovePlatformServer_Implementation(float DesiredX)
{
	DesiredXAcceleration = DesiredX;
	LastServerAckPosition = GetActorLocation();
}

void APlatformPawn::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APlatformPawn, DesiredXAcceleration);
	DOREPLIFETIME(APlatformPawn, LastServerAckPosition);
}

void APlatformPawn::OnRep_LastServerAckPosition()
{
	const float PositionErrorTolerance = 50.0f;
	if(FVector::Distance(GetActorLocation(), LastServerAckPosition) > PositionErrorTolerance)
	{
		SetActorLocation(LastServerAckPosition, true);
	}
}

