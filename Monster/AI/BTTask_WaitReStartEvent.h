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
	//�ش� ��忡�� AIController�� ���ؼ� ���� ���¿�����
	//�ִϸ��̼��� ���� ����� ������ Tree�� �����.
	//�� Task�� ����ϸ� �ش� �ִϸ��̼��� �� �κп� AnimNotify_ReStartBT�� �־����.
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
