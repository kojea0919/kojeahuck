// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SelectAttackType.h"
#include "Monster/Bear/BearMonster.h"
#include "Monster/MonsterAIController.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetStringLibrary.h"

EBTNodeResult::Type UBTTask_SelectAttackType::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AMonsterAIController * pController = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());
	if (!pController)
	{
		return EBTNodeResult::Failed;
	}

	ABearMonster * pBear = Cast<ABearMonster>(pController->GetPawn());
	if (!pBear)
	{
		return EBTNodeResult::Failed;
	}

	int iAttackType = UKismetMathLibrary::RandomIntegerInRange(1, 3);
	FString AttackTypeName = "Attack";
	AttackTypeName.Append(UKismetStringLibrary::Conv_IntToString(iAttackType));

	pBear->S2A_PlayPatternMontage((FName)*AttackTypeName);
	
	return EBTNodeResult::Succeeded;
}
