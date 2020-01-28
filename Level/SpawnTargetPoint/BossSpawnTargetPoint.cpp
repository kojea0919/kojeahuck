// Fill out your copyright notice in the Description page of Project Settings.


#include "BossSpawnTargetPoint.h"
#include "Monster/Boss/Boss.h"
#include "Engine/World.h"

void ABossSpawnTargetPoint::BeginPlay()
{
	Super::BeginPlay();
}

AActor * ABossSpawnTargetPoint::Spawn()
{
	return GetWorld()->SpawnActor<ABoss>(Boss_Template, GetActorLocation(), GetActorRotation());
}
