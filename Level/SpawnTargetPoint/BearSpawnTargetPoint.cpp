// Fill out your copyright notice in the Description page of Project Settings.


#include "BearSpawnTargetPoint.h"
#include "Monster/Bear/BearMonster.h"
#include "Engine/World.h"

void ABearSpawnTargetPoint::BeginPlay()
{
	Super::BeginPlay();
}

AActor * ABearSpawnTargetPoint::Spawn()
{
	return GetWorld()->SpawnActor<ABearMonster>(Bear_Template,GetActorLocation(),GetActorRotation());
}
