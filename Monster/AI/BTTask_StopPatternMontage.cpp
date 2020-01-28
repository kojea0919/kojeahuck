// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_StopPatternMontage.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Monster/MonsterAIController.h"
#include "Monster/Boss/Boss.h"
#include "Monster/MonsterBase.h"

EBTNodeResult::Type UBTTask_StopPatternMontage::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AMonsterAIController * pController = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());
	if (!pController)
		return EBTNodeResult::Failed;

	AMonsterBase * pMonster = Cast<AMonsterBase>(pController->GetPawn());
	if(!pMonster)
		return EBTNodeResult::Failed;

	//패턴이 재생중이면 멈추기
	if (pMonster->IsPlayingPattern())
	{
		pMonster->StopPatternMontage();

		ABoss * pBoss = Cast<ABoss>(pMonster);
		if (pBoss)
			pBoss->SetPattern2Particle(false);

	}

	return EBTNodeResult::Succeeded;
}
