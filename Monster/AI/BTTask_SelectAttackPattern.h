// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_SelectAttackPattern.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UBTTask_SelectAttackPattern : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	//보스가 플레이어와의 거리에 따라서 원거리 공격을 할지 근거리 공격을 할지 택한다.
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
