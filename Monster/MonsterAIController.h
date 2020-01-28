// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Monster/MonsterBase.h"
#include "MonsterAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API AMonsterAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AMonsterAIController();


	//Components
	//----------------------------------------------
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBehaviorTreeComponent* BTComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBlackboardComponent* BBComponent;
	//----------------------------------------------

	
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
	


	//BlackBoard Set�Լ�
	//-------------------------------------
	
	//SetTarget�Լ� : ������ ��ġ ����
	//---------------------------------
	void SetTarget(FVector NewTarget);
	//---------------------------------

	//SetState�Լ� : ���� Monster���� ����
	//---------------------------------
	void SetState(EMonsterState NewState);
	//---------------------------------

	//SetPlayer�Լ� : ���� Target������ Player ����
	//-------------------------------------
	void SetPlayer(AActor * Target);
	//-------------------------------------

	//SetReStart�Լ� : ���� ����Ǵ� Logic�� ReStart���� ���� ����
	//-----------------------------------------------------------
	void SetReStart(bool bIsReStart);
	//-----------------------------------------------------------

	//-------------------------------------
	//BlackBoard Set�Լ�


	//BehaviorTree Stop,ReStart�Լ�
	//------------------------------------
	void StopBT();

	void ReStartBT();
	//------------------------------------
	//BehaviorTree Stop,ReStart�Լ�
};