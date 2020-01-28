// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SetTargetPlayer.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Basic/BasicGM.h"
#include "Engine/World.h"
#include "Monster/MonsterAIController.h"

EBTNodeResult::Type UBTTask_SetTargetPlayer::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	ABasicGM * pGM = Cast<ABasicGM>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!pGM)
		return EBTNodeResult::Failed;

	AMonsterAIController * pController = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());
	if (!pController)
	{
		return EBTNodeResult::Failed;
	}
	
	AMonsterBase * pMonster = Cast<AMonsterBase>(pController->GetPawn());
	if(!pMonster)
	{
		return EBTNodeResult::Failed;
	}

	FVector MonsterLocation = pMonster->GetActorLocation();

	//살아있는 플레이어 배열 가져오기
	TArray<APlayerController*> PC_Array = pGM->AlivePlayer;
	
	float fMinDist = 99999999999999;
	AActor * pTargetPlayer = nullptr;


	//가장 가까운 플레이어 찾기
	for (int iCnt = 0; iCnt < PC_Array.Num(); ++iCnt)
	{
		AActor * pPlayer = PC_Array[iCnt]->GetPawn();

		if (pPlayer)
		{
			FVector PlayerLocation = pPlayer->GetActorLocation();

			float fCurDist = (PlayerLocation - MonsterLocation).SizeSquared();


			if (fMinDist > fCurDist)
			{
				fMinDist = fCurDist;
				pTargetPlayer = pPlayer;
			}
		}
	}

	if(nullptr == pTargetPlayer)
		return EBTNodeResult::Failed;

	pController->SetPlayer(pTargetPlayer);
	pMonster->TargetPlayer = Cast<APlayerBase>(pTargetPlayer);

	return EBTNodeResult::Succeeded;
}
