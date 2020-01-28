// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "SpawnTargetPoint.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API ASpawnTargetPoint : public ATargetPoint
{
	GENERATED_BODY()
	

protected:
	virtual void BeginPlay() override;

public:
	virtual AActor * Spawn();
};
