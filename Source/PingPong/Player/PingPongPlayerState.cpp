// Fill out your copyright notice in the Description page of Project Settings.


#include "PingPongPlayerState.h"

void APingPongPlayerState::AddScore()
{
	SetScore(GetScore() + 1);
}

void APingPongPlayerState::OnRep_Score()
{
	Super::OnRep_Score();
	OnScoreUpdated.Broadcast();
}
