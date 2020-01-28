// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "TriggerBox_Stage.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API ATriggerBox_Stage : public ATriggerBox
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;


	//이 Stage의 몬스터 배열
	//----------------------------------------------------------
	TArray<class AMonsterBase *> StageMonster;
	//----------------------------------------------------------
	//이 Stage의 몬스터 배열


public:
	ATriggerBox_Stage();

	//Stage 시작 또는 Stage Clear시 호출될 함수
	virtual void StageStart();
	virtual void StageClear();


	//RemoveMonster
	//Monster배열에서 해당 몬스터를 삭제시킨다.
	//------------------------------------------------------
	void RemoveMonster(class AMonsterBase * pTargetMonster);
	//------------------------------------------------------
};
