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
	//������ �÷��̾���� �Ÿ��� ���� ���Ÿ� ������ ���� �ٰŸ� ������ ���� ���Ѵ�.
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};