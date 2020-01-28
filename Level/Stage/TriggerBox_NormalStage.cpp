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
	//���������� ����
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

	//�÷��̾ Ʈ���ſ� �������Ǹ� �������� ����
	APlayerBase * pPlayer = Cast<APlayerBase>(OtherActor);
	if (pPlayer)
	{
		StageStart();
	}
}