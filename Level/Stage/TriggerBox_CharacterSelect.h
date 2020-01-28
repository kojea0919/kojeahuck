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
	//Stage ���� �Ǵ� Stage Clear�� ȣ��� �Լ�
	virtual void StageStart() override;
	virtual void StageClear() override;

	//���� ĳ���� ������ ���� �÷��̾� list
	TArray<class APlayerBase*> PlayerList;

	//���� Stage�� ���� �� ���Ƴ��� ���� Actor
	//----------------------------------------------------------
	AActor * Wall;
	//----------------------------------------------------------

	void RemovePlayer(class APlayerBase * pPlayer);

private:
	int AllPlayerCnt;
};
