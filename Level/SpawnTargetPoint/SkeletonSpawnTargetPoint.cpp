// Fill out your copyright notice in the Description page of Project Settings.


#include "SkeletonSpawnTargetPoint.h"
#include "Monster/Skeleton/SkeletonMonster.h"
#include "Engine/World.h"

void ASkeletonSpawnTargetPoint::BeginPlay()
{
	Super::BeginPlay();
}


AActor * ASkeletonSpawnTargetPoint::Spawn()
{
	return GetWorld()->SpawnActor<ASkeletonMonster>(Skeleton_Template, GetActorLocation(),GetActorRotation());
}
