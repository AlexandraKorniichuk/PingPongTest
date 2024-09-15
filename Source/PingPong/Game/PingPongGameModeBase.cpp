// Copyright Epic Games, Inc. All Rights Reserved.


#include "PingPongGameModeBase.h"

#include "PingPongPlayerState.h"
#include "PlatformController.h"
#include "GameFramework/GameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "PingPong/FreePlayerStart.h"
#include "PingPong/Gate.h"

AActor* APingPongGameModeBase::ChoosePlayerStart_Implementation(AController* Player)
{
	TArray<AActor*> FoundStarts;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFreePlayerStart::StaticClass(), FoundStarts);
	for (auto Start : FoundStarts)
	{
		AFreePlayerStart* FreeStart = Cast<AFreePlayerStart>(Start);
		if (FreeStart->IsFree)
		{
			FreeStart->IsFree = false;
			return FreeStart;
		}
	}
	return Super::ChoosePlayerStart_Implementation(Player);
}

void APingPongGameModeBase::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);
	
	APlatformController* Controller = Cast<APlatformController>(NewPlayer);
	Players.Add(Controller);

	APingPongPlayerState* PlayerState = Cast<APingPongPlayerState>(Controller->PlayerState);
	TakeFreeGate(PlayerState);

	if (Players.Num() == 2)
	{
		UpdatePlayersUI();
	}
}

void APingPongGameModeBase::TakeFreeGate(APingPongPlayerState* PlayerState)
{
	TArray<AActor*> FoundGates;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGate::StaticClass(), FoundGates);
	for (int i = FoundGates.Num() - 1; i >= 0; i--)
	{
		AGate* FreeGate = Cast<AGate>(FoundGates[i]);
		if (!FreeGate->PlayerState)
		{
			FreeGate->PlayerState = PlayerState;
			break;
		}
	}
}

void APingPongGameModeBase::UpdatePlayersUI()
{
	for(auto Player : Players)
	{
		Player->UpdateUI();
	}
}