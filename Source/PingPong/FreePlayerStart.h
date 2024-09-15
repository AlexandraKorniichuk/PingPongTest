// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "FreePlayerStart.generated.h"

/**
 * 
 */
UCLASS()
class PINGPONG_API AFreePlayerStart : public APlayerStart
{
	GENERATED_BODY()

public:
	bool IsFree = true;
	
};
