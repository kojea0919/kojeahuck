// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_GoToAttackRange.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Monster/MonsterAIController.h"
#include "Monster/MonsterBase.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/CapsuleComponent.h"

EBTNodeResult::Type UBTTask_GoToAttackRange::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn * Player = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("Player")));
	AMonsterBase * Monster = Cast<AMonsterBase>(OwnerComp.GetAIOwner()->GetPawn());
	if (!Player || !Monster)
	{
		return EBTNodeResult::Failed;
	}


	//���Ϳ��� �÷��̾�� ���� normal ����
	FVector MonsterToPlayer = (Player->GetActorLocation() - Monster->GetActorLocation());
	float Distance = MonsterToPlayer.Size2D();
	MonsterToPlayer = UKismetMathLibrary::Normal(MonsterToPlayer);

	//Max�� ���� ������ ��Ÿ� ����s�� �ִ� ��쿡�� �� �����̵��� �ϱ�����
	float DistanceToGo = UKismetMathLibrary::Max(0, Distance - Monster->AttackRange + Monster->GetCapsuleComponent()->GetScaledCapsuleRadius() * 1.2f);

	//������ ���� ��Ÿ���ŭ ���� �Ÿ����� �߰�
	FVector NewLocation = MonsterToPlayer * DistanceToGo + Monster->GetActorLocation();
	
	AMonsterAIController * AIController = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());
	if (!AIController)
	{
		UE_LOG(LogClass, Warning, TEXT("2"));

		return EBTNodeResult::Failed;
	}

	AIController->SetTarget(NewLocation);
	
	return EBTNodeResult::Succeeded;
}