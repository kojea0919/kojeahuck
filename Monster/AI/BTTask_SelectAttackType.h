// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_SelectAttackType.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UBTTask_SelectAttackType : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	//몬스터의 기본 공격 모션중 랜덤으로 하나를 택하여 재생한다.
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
