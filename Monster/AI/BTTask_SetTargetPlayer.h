// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_SetTargetPlayer.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UBTTask_SetTargetPlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	//현재 살아있는 플레이어중 가장 가까이 있는 플레이어를 Target으로 정한다.
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
