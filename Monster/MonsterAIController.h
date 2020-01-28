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
	


	//BlackBoard Set함수
	//-------------------------------------
	
	//SetTarget함수 : 움직일 위치 설정
	//---------------------------------
	void SetTarget(FVector NewTarget);
	//---------------------------------

	//SetState함수 : 현재 Monster상태 설정
	//---------------------------------
	void SetState(EMonsterState NewState);
	//---------------------------------

	//SetPlayer함수 : 현재 Target으로할 Player 설정
	//-------------------------------------
	void SetPlayer(AActor * Target);
	//-------------------------------------

	//SetReStart함수 : 현재 실행되는 Logic이 ReStart상태 인지 설정
	//-----------------------------------------------------------
	void SetReStart(bool bIsReStart);
	//-----------------------------------------------------------

	//-------------------------------------
	//BlackBoard Set함수


	//BehaviorTree Stop,ReStart함수
	//------------------------------------
	void StopBT();

	void ReStartBT();
	//------------------------------------
	//BehaviorTree Stop,ReStart함수
};