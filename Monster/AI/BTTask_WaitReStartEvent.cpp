// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_WaitReStartEvent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Monster/MonsterAIController.h"

EBTNodeResult::Type UBTTask_WaitReStartEvent::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AMonsterAIController * pAIController = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());
	if (!pAIController)
		return EBTNodeResult::Failed;

	pAIController->StopBT();

	return EBTNodeResult::Succeeded;
}
