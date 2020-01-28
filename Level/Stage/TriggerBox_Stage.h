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


	//�� Stage�� ���� �迭
	//----------------------------------------------------------
	TArray<class AMonsterBase *> StageMonster;
	//----------------------------------------------------------
	//�� Stage�� ���� �迭


public:
	ATriggerBox_Stage();

	//Stage ���� �Ǵ� Stage Clear�� ȣ��� �Լ�
	virtual void StageStart();
	virtual void StageClear();


	//RemoveMonster
	//Monster�迭���� �ش� ���͸� ������Ų��.
	//------------------------------------------------------
	void RemoveMonster(class AMonsterBase * pTargetMonster);
	//------------------------------------------------------
};
