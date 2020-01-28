// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_CheckResetMoveTo.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Monster/MonsterAIController.h"
#include "Monster/MonsterBase.h"
#include "Kismet/KismetMathLibrary.h"

EBTNodeResult::Type UBTTask_CheckResetMoveTo::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	APawn * Player = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("Player")));
	AMonsterBase * Monster = Cast<AMonsterBase>(OwnerComp.GetAIOwner()->GetPawn());
	if (!Player || !Monster)
	{
		return EBTNodeResult::Failed;
	}


	//몬스터에서 플레이어로 가는 normal 벡터
	FVector MonsterToPlayer = (Player->GetActorLocation() - Monster->GetActorLocation());
	float Distance = MonsterToPlayer.Size2D();


	if (Distance > 700.f)
	{
		AMonsterAIController * AIController = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());
		if (AIController)
		{
			AIController->ReStartBT();
		}
		return EBTNodeResult::Failed;
	}


	return EBTNodeResult::Succeeded;
}
