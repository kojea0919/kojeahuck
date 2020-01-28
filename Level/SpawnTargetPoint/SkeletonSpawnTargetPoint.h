// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Level/SpawnTargetPoint/SpawnTargetPoint.h"
#include "SkeletonSpawnTargetPoint.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API ASkeletonSpawnTargetPoint : public ASpawnTargetPoint
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual AActor * Spawn() override;

	//생성시킬 Mosnter Blueprint
	//-----------------------------------------
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSubclassOf<class ASkeletonMonster> Skeleton_Template;
	//-----------------------------------------
};
