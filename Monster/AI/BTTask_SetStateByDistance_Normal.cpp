//// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SetStateByDistance_Normal.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Monster/MonsterAIController.h"
#include "Monster/MonsterBase.h"

EBTNodeResult::Type UBTTask_SetStateByDistance_Normal::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn * Player = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("Player")));
	AMonsterAIController * AIController = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());
	AMonsterBase * Monster = Cast<AMonsterBase>(AIController->GetPawn());

	if (!Player || !AIController || !Monster)
		return EBTNodeResult::Failed;

	//현재 플레이어와의 거리 구하기
	float Distance = (Player->GetActorLocation() - Monster->GetActorLocation()).Size2D();

	AIController->SetReStart(false);

	//현재 거리가 몬스터 공격범위보다 작거나 같으면
	if (Distance <= Monster->AttackRange)
	{
		//몬스터 상태를 공격 상태로 바꾸기
		Monster->SetState(EMonsterState::Attack);
	}
	//거리가 몬스터 공격범위보다 크면
	else
	{
		//몬스터 상태를 TargetOn 상태로 바꾸기
		Monster->SetState(EMonsterState::TargetOn);
	}

	return EBTNodeResult::Succeeded;
}