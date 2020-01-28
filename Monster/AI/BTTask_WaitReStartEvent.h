// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_WaitReStartEvent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UBTTask_WaitReStartEvent : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	//해당 노드에서 AIController를 통해서 현재 상태에대한
	//애니메이션이 전부 재생될 때까지 Tree를 멈춘다.
	//이 Task를 사용하면 해당 애니메이션의 끝 부분에 AnimNotify_ReStartBT를 넣어야함.
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
