// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Level/SpawnTargetPoint/SpawnTargetPoint.h"
#include "BossSpawnTargetPoint.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API ABossSpawnTargetPoint : public ASpawnTargetPoint
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

public:
	virtual AActor * Spawn() override;

	//������ų Mosnter Blueprint
	//-----------------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class ABoss> Boss_Template;
	//-----------------------------------------
	//������ų Mosnter Blueprint
};
