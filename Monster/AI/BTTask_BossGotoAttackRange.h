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
	//자기 주변에 Player를 찾아서 특정 거리안에 있으면 이동해서 공격
	//특정 거리를 넘으면 해당 플레이어 주변으로 텔레포트 한다.
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
