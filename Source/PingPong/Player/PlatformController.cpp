// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformController.h"

#include "Blueprint/UserWidget.h"

APlatformController::APlatformController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APlatformController::BeginPlay()
{
	Super::BeginPlay();

	if (GetLocalPlayer())
	{
		CreateWidgetIfNull();
	}
}

void APlatformController::CreateWidgetIfNull()
{
	if (Widget == nullptr)
	{
		Widget = CreateWidget<UUserWidget>(this, WidgetClass);
		Widget->AddToViewport();
	}
}

void APlatformController::UpdateUI()
{
	ClientUpdateUI();
}

void APlatformController::ClientUpdateUI_Implementation()
{
	if(Widget == nullptr)
	{
		CreateWidgetIfNull();
	}
	OnStart.Broadcast();
}