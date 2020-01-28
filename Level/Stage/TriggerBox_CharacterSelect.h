// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Level/Stage/TriggerBox_Stage.h"
#include "TriggerBox_CharacterSelect.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API ATriggerBox_CharacterSelect : public ATriggerBox_Stage
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

public:
	//Stage 시작 또는 Stage Clear시 호출될 함수
	virtual void StageStart() override;
	virtual void StageClear() override;

	//아직 캐릭터 선택을 안한 플레이어 list
	TArray<class APlayerBase*> PlayerList;

	//다음 Stage로 가는 길 막아놓기 위한 Actor
	//----------------------------------------------------------
	AActor * Wall;
	//----------------------------------------------------------

	void RemovePlayer(class APlayerBase * pPlayer);

private:
	int AllPlayerCnt;
};
