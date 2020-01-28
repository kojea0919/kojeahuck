// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerBox_LastStage.h"
#include "Player/PlayerBase.h"
#include "Level/SpawnTargetPoint/BossSpawnTargetPoint.h"
#include "Monster/Boss/Boss.h"
#include "Kismet/GameplayStatics.h"
#include "Basic/BasicPC.h"
#include "Basic/BasicGM.h"
#include "Engine/World.h"

ATriggerBox_LastStage::ATriggerBox_LastStage()
{
	OnActorBeginOverlap.AddDynamic(this, &ATriggerBox_LastStage::OnOverlapBegin);

}

void ATriggerBox_LastStage::BeginPlay()
{
	Super::BeginPlay();
}

void ATriggerBox_LastStage::StageStart()
{
	if (GetWorld()->IsServer())
	{
		TArray<AActor*> TargetPoints;

		GetOverlappingActors(TargetPoints, ASpawnTargetPoint::StaticClass());


		for (int iCnt = 0; iCnt < TargetPoints.Num(); ++iCnt)
		{
			ASpawnTargetPoint * pTargetPoint = Cast<ASpawnTargetPoint>(TargetPoints[iCnt]);

			AActor * pSpawnActor = pTargetPoint->Spawn();
			ABoss * pBoss = Cast<ABoss>(pSpawnActor);
			if (pBoss)
			{
				StageMonster.Add(pBoss);
				pBoss->AddStage(this);
			}
		}

		bIsStarted = true;
	}
}

void ATriggerBox_LastStage::StageClear()
{
	ABasicGM * pGM = Cast<ABasicGM>(UGameplayStatics::GetGameMode(GetWorld()));
	if (pGM)
	{
		pGM->GameClear();
	}
}


void ATriggerBox_LastStage::OnOverlapBegin(AActor * OverlappedActor, AActor * OtherActor)
{
	if (bIsStarted)
		return;

	//플레이어가 트리거와 오버랩되면 스테이지 시작
	APlayerBase * pPlayer = Cast<APlayerBase>(OtherActor);
	if (pPlayer)
	{
		StageStart();
	}
}
