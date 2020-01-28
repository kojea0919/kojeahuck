// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SelectAttackPattern.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Monster/Boss/Boss.h"
#include "Monster/MonsterAIController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/World.h"
#include "Particles/ParticleSystemComponent.h"




EBTNodeResult::Type UBTTask_SelectAttackPattern::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AMonsterAIController * pController = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());
	if (!pController)
	{
		return EBTNodeResult::Failed;
	}
	
	ABoss * pBoss = Cast<ABoss>(pController->GetPawn());
	if (!pBoss)
	{
		return EBTNodeResult::Failed;
	}

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel1));
	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(pBoss);
	TArray<AActor*> OutActors;


	//범위 안에 Player가 있는지 확인
	bool bResult = UKismetSystemLibrary::SphereOverlapActors(pBoss->GetWorld(),
		pBoss->GetActorLocation(),
		pBoss->AttackRange + 300.0f,
		ObjectTypes,
		AActor::StaticClass(),
		IgnoreActors,
		OutActors);

	if (bResult)
	{
		//Player가 범위 안에 없으면 Pattern1 
		pBoss->SetState(EMonsterState::Pattern1);
	    FString PatternName = "Pattern1";
		pBoss->S2A_PlayPatternMontage((FName)*PatternName);
	}

	else
	{
		pBoss->SetState(EMonsterState::Pattern2);
		FString PatternName = "Pattern2";
		pBoss->S2A_PlayPatternMontage((FName)*PatternName);
	}

	return EBTNodeResult::Succeeded;
}