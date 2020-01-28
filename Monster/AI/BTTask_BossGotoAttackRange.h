// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_BossGotoAttackRange.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UBTTask_BossGotoAttackRange : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	//�ڱ� �ֺ��� Player�� ã�Ƽ� Ư�� �Ÿ��ȿ� ������ �̵��ؼ� ����
	//Ư�� �Ÿ��� ������ �ش� �÷��̾� �ֺ����� �ڷ���Ʈ �Ѵ�.
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
