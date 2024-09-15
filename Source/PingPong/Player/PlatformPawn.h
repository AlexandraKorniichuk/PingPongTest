// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlatformPawn.generated.h"

UCLASS()
class PINGPONG_API APlatformPawn : public APawn
{
	GENERATED_BODY()

public:
	APlatformPawn();
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Mesh")
	UStaticMeshComponent* PlatformMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Movement")
    float MoveSpeed = 1000.0f;
	
	UFUNCTION()
	void Move(float AxisValue);
	
	UFUNCTION()
	void OnRep_LastServerAckPosition();

	UFUNCTION(Server, Reliable)
	void MovePlatformServer(float DesiredX);

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	UPROPERTY(Replicated)
	float DesiredXAcceleration = 0.0f;
	
	float LastXAxisInputValue = 0.0f;
	
	UPROPERTY(ReplicatedUsing = OnRep_LastServerAckPosition)
	FVector LastServerAckPosition = FVector::ZeroVector;
};
