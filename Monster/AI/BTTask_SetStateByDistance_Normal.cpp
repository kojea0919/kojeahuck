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

	//���� �÷��̾���� �Ÿ� ���ϱ�
	float Distance = (Player->GetActorLocation() - Monster->GetActorLocation()).Size2D();

	AIController->SetReStart(false);

	//���� �Ÿ��� ���� ���ݹ������� �۰ų� ������
	if (Distance <= Monster->AttackRange)
	{
		//���� ���¸� ���� ���·� �ٲٱ�
		Monster->SetState(EMonsterState::Attack);
	}
	//�Ÿ��� ���� ���ݹ������� ũ��
	else
	{
		//���� ���¸� TargetOn ���·� �ٲٱ�
		Monster->SetState(EMonsterState::TargetOn);
	}

	return EBTNodeResult::Succeeded;
}