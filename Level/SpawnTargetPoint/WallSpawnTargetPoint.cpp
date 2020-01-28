// Fill out your copyright notice in the Description page of Project Settings.


#include "WallSpawnTargetPoint.h"
#include "Engine/World.h"

void AWallSpawnTargetPoint::BeginPlay()
{
	Super::BeginPlay();
}

AWallSpawnTargetPoint::AWallSpawnTargetPoint()
{
}

AActor * AWallSpawnTargetPoint::Spawn()
{
	return GetWorld()->SpawnActor<AActor>(Wall_Template, GetActorLocation(), GetActorRotation());
}
