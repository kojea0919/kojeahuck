// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_BossGotoAttackRange.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Monster/MonsterAIController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/World.h"
#include "Monster/Boss/Boss.h"

EBTNodeResult::Type UBTTask_BossGotoAttackRange::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AMonsterAIController * pAIController = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());
	ABoss * pBoss = Cast<ABoss>(pAIController->GetPawn());
	APawn * pPlayer = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("Player")));

	if (!pAIController || !pBoss || !pPlayer)
		return EBTNodeResult::Failed;

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel1));
	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(pBoss);
	TArray<AActor*> OutActors;

	//범위 안에 Player가 있는지 확인
	bool bResult = UKismetSystemLibrary::SphereOverlapActors(pBoss->GetWorld(),
		pBoss->GetActorLocation(),
		1200.0f, 
		ObjectTypes,
		AActor::StaticClass(),
		IgnoreActors,
		OutActors);

	if(!bResult)
	{
		//Player가 1200 범위 안에 없으면 텔레포트 
		pBoss->SetState(EMonsterState::Teleport);
	}

	return EBTNodeResult::Succeeded;
}
