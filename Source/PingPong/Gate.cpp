// Fill out your copyright notice in the Description page of Project Settings.


#include "Gate.h"

#include "PingPongPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Ball.h"
#include "Components/BoxComponent.h"
#include "Net/UnrealNetwork.h"


AGate::AGate()
{
	PrimaryActorTick.bCanEverTick = false;
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
}

void AGate::BeginPlay()
{
	Super::BeginPlay();

	if (Trigger)
	{
		Trigger->OnComponentBeginOverlap.AddDynamic(this, &AGate::OnOverlapBegin);
	}
}

void AGate::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (auto Ball = Cast<ABall>(OtherActor))
	{
		Ball->ResetLocation();
	}
	
	if (GetLocalRole() == ROLE_Authority)
	{
		TArray<AActor*> FoundPlayerStates;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APingPongPlayerState::StaticClass(), FoundPlayerStates);
		FoundPlayerStates.RemoveSwap(PlayerState);

		if(FoundPlayerStates.Num())
		{
			if(APingPongPlayerState* OtherPlayerState = Cast<APingPongPlayerState>(FoundPlayerStates[0]))
			{
				OtherPlayerState->AddScore();
			}
		}
	}
}

void AGate::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(AGate, PlayerState);
}
