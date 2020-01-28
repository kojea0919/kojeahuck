// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Level/SpawnTargetPoint/SpawnTargetPoint.h"
#include "WallSpawnTargetPoint.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API AWallSpawnTargetPoint : public ASpawnTargetPoint
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	AWallSpawnTargetPoint();

	virtual AActor * Spawn() override;

	//다음 Stage로 가는 길을 막을 벽
	//-----------------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AActor> Wall_Template;
	//-----------------------------------------
};
