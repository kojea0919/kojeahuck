// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_CheckResetMoveTo.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UBTTask_CheckResetMoveTo : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	//플레이어의 위치와 몬스터가 가고있는 목적지의 차이가 많이나면
	//새로 목적지를 계산하여 가도록 처음부터 다시 실행한다.
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
