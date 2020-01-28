// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerBox_NormalStage.h"
#include "Level/SpawnTargetPoint/SkeletonSpawnTargetPoint.h"
#include "Player/PlayerBase.h"
#include "Monster/MonsterBase.h"
#include "Engine/World.h"
ATriggerBox_NormalStage::ATriggerBox_NormalStage()
{
	OnActorBeginOverlap.AddDynamic(this, &ATriggerBox_NormalStage::OnOverlapBegin);
}

void ATriggerBox_NormalStage::BeginPlay()
{
	Super::BeginPlay();

}

void ATriggerBox_NormalStage::StageStart()
{
	//서버에서만 실행
	if (GetWorld()->IsServer())
	{
		TArray<AActor*> TargetPoints;

		GetOverlappingActors(TargetPoints, ASpawnTargetPoint::StaticClass());

		for (int iCnt = 0; iCnt < TargetPoints.Num(); ++iCnt)
		{
			ASpawnTargetPoint * pTargetPoint = Cast<ASpawnTargetPoint>(TargetPoints[iCnt]);

			AActor * pSpawnActor = pTargetPoint->Spawn();
			AMonsterBase * pMonster = Cast<AMonsterBase>(pSpawnActor);
			if (pMonster)
			{
				StageMonster.Add(pMonster);
				pMonster->AddStage(this);
			}
			else
				Wall = pSpawnActor;

		}

		bIsStarted = true;
	}
}

void ATriggerBox_NormalStage::StageClear()
{
	if(Wall)
		Wall->Destroy();
}

void ATriggerBox_NormalStage::OnOverlapBegin(AActor * OverlappedActor, AActor * OtherActor)
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