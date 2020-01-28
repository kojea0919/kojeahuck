// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_SetStateByDistance_Normal.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UBTTask_SetStateByDistance_Normal : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	//기본 몬스터와 플레이어 간의 거리를 구하여 기본 몬스터의 상태를 정한다.
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
