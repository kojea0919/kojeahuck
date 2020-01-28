// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Level/Stage/TriggerBox_Stage.h"
#include "TriggerBox_NormalStage.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API ATriggerBox_NormalStage : public ATriggerBox_Stage
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:

	ATriggerBox_NormalStage();

	UFUNCTION()
	void OnOverlapBegin(AActor * OverlappedActor, AActor * OtherActor);

	//Stage 시작 또는 Stage Clear시 호출될 함수
	virtual void StageStart() override;
	virtual void StageClear() override;

	//Spawn할 몬스터 종류
	//----------------------------------------------------------
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSubclassOf<class ASkeletonSpawnTargetPoint> SkeletonTargetPoint_Template;
	//----------------------------------------------------------
	//Spawn할 몬스터 종류


	//다음 Stage로 가는 길 막아놓기 위한 Actor
	//----------------------------------------------------------
	AActor * Wall;
	//----------------------------------------------------------


private:
	//Stage 한번만 시작하도록 하는 bool변수
	//---------------------------------
	bool bIsStarted = false;
	//---------------------------------
};
