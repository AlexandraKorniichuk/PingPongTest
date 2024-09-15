// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlatformController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartEvent);

class UUserWidget;

UCLASS()
class PINGPONG_API APlatformController : public APlayerController
{
	GENERATED_BODY()

public:
	APlatformController();

protected:
	virtual void BeginPlay() override;

private:
	void CreateWidgetIfNull();

public:		
	void UpdateUI();

	UFUNCTION(BlueprintCallable, Client, Reliable)
	void ClientUpdateUI();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable, Category="Start events")
	FStartEvent OnStart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI")
	UUserWidget* Widget;
	
	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UUserWidget> WidgetClass;
	
};
