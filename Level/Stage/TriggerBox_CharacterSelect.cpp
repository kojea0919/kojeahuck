// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerBox_CharacterSelect.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Basic/BasicGM.h"
#include "Basic/MyGameInstance.h"
#include "WaitMap/WaitMapPlayer.h"
#include "Level/SpawnTargetPoint/WallSpawnTargetPoint.h"
#include "Engine/World.h"

void ATriggerBox_CharacterSelect::BeginPlay()
{
	Super::BeginPlay();

	ABasicGM * pGM = Cast<ABasicGM>(UGameplayStatics::GetGameMode(GetWorld()));
	if (pGM)
		pGM->CharacterTriggerCreate(this);

}

void ATriggerBox_CharacterSelect::StageStart()
{
	ABasicGM * pGM = Cast<ABasicGM>(UGameplayStatics::GetGameMode(GetWorld()));

	if (!pGM)
	{
		return;
	}

	TArray<ABasicPC*> PlayerControllers = pGM->AllPlayer;

	for (int iCnt = 0; iCnt < PlayerControllers.Num(); ++iCnt)
	{
		AWaitMapPlayer * pCurPlayer = Cast<AWaitMapPlayer>(PlayerControllers[iCnt]->GetPawn());
		if (pCurPlayer)
		{
			PlayerList.Push(pCurPlayer);
			pCurPlayer->SetCharacterSelectTrigger(this);
		}
	}

	TArray<AActor*> TargetPoints;

	GetOverlappingActors(TargetPoints, ASpawnTargetPoint::StaticClass());

	for (int iCnt = 0; iCnt < TargetPoints.Num(); ++iCnt)
	{
		ASpawnTargetPoint * pTargetPoint = Cast<ASpawnTargetPoint>(TargetPoints[iCnt]);
		Wall = pTargetPoint->Spawn();
	}
}

void ATriggerBox_CharacterSelect::StageClear()
{
	if(Wall)
		Wall->Destroy();
}

void ATriggerBox_CharacterSelect::RemovePlayer(APlayerBase * pPlayer)
{
	PlayerList.Remove(pPlayer);
	if (PlayerList.Num() == 0)
	{
		StageClear();
	}
}
