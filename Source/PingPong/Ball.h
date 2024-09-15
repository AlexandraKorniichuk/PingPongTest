// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"

class USphereComponent;

UCLASS()
class PINGPONG_API ABall : public AActor
{
	GENERATED_BODY()
	
public:	
	ABall();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Mesh")
	UStaticMeshComponent* Mesh;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Movement")
	float MoveSpeed = 100.0f;
	
	virtual void BeginPlay() override;

	UPROPERTY(Replicated)
	FVector MovementVector = FVector(0.5f, 0.5f, 0.0f);
	
public:	
	virtual void Tick(float DeltaTime) override;

	void ResetLocation();

private:
	FVector StartLocation;
};
