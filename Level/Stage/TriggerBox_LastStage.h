// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Level/Stage/TriggerBox_Stage.h"
#include "TriggerBox_LastStage.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API ATriggerBox_LastStage : public ATriggerBox_Stage
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;


public:

	ATriggerBox_LastStage();

	UFUNCTION()
		void OnOverlapBegin(AActor * OverlappedActor, AActor * OtherActor);

	//Stage 시작 또는 Stage Clear시 호출될 함수
	virtual void StageStart() override;
	virtual void StageClear() override;

	//Spawn할 몬스터 종류
	//----------------------------------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class ABossSpawnTargetPoint> SkeletonTargetPoint_Template;
	//----------------------------------------------------------
	//Spawn할 몬스터 종류

private:
	//Stage 한번만 시작하도록 하는 bool변수
	//---------------------------------
	bool bIsStarted = false;
	//---------------------------------
};
