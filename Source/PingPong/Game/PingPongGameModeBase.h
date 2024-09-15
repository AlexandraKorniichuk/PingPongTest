// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "PingPongGameModeBase.generated.h"

class APingPongPlayerState;
class APlatformController;

UCLASS()
class PINGPONG_API APingPongGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

private:
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

	virtual void OnPostLogin(AController* NewPlayer) override;

	void TakeFreeGate(APingPongPlayerState* PlayerState);

	TArray<APlatformController*> Players;

	void UpdatePlayersUI();	
};
