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

	//Stage ���� �Ǵ� Stage Clear�� ȣ��� �Լ�
	virtual void StageStart() override;
	virtual void StageClear() override;

	//Spawn�� ���� ����
	//----------------------------------------------------------
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSubclassOf<class ASkeletonSpawnTargetPoint> SkeletonTargetPoint_Template;
	//----------------------------------------------------------
	//Spawn�� ���� ����


	//���� Stage�� ���� �� ���Ƴ��� ���� Actor
	//----------------------------------------------------------
	AActor * Wall;
	//----------------------------------------------------------


private:
	//Stage �ѹ��� �����ϵ��� �ϴ� bool����
	//---------------------------------
	bool bIsStarted = false;
	//---------------------------------
};
