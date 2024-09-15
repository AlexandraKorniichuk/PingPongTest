// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gate.generated.h"

class UBoxComponent;
class APingPongPlayerState;

UCLASS()
class PINGPONG_API AGate : public AActor
{
	GENERATED_BODY()
	
public:	
	AGate();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:	
	UPROPERTY(VisibleAnywhere, Category="Collision")
	UBoxComponent* Trigger;

	void SetPlayerState(APingPongPlayerState* NewPlayerState) { PlayerState = NewPlayerState; }

	UPROPERTY(BlueprintReadOnly, Replicated)
	APingPongPlayerState* PlayerState;
};
