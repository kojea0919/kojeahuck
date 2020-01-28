// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_StopPatternMontage.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UBTTask_StopPatternMontage : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	//몬스터가 죽었을 경우 현재 실행중이던 Montage를 멈추도록 한다.
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
