// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PingPongPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FScoreEvent);

UCLASS()
class PINGPONG_API APingPongPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable, Category="Score events")
	FScoreEvent OnScoreUpdated;

	void AddScore();
	virtual void OnRep_Score() override;
};
