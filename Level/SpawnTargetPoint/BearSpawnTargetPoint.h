// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Level/SpawnTargetPoint/SpawnTargetPoint.h"
#include "BearSpawnTargetPoint.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API ABearSpawnTargetPoint : public ASpawnTargetPoint
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	virtual AActor * Spawn() override;

	//생성시킬 Mosnter Blueprint
	//-----------------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category="SpawnTarget")
	TSubclassOf<class ABearMonster> Bear_Template;
	//-----------------------------------------
	//생성시킬 Mosnter Blueprint
};
