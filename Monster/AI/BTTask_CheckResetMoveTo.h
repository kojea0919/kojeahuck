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
	//�÷��̾��� ��ġ�� ���Ͱ� �����ִ� �������� ���̰� ���̳���
	//���� �������� ����Ͽ� ������ ó������ �ٽ� �����Ѵ�.
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
