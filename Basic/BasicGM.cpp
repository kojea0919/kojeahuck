// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicGM.h"
#include "Basic/MyGameInstance.h"
#include "Player/Countess/Countess.h"
#include "Player/Greystone/Greystone.h"
#include "Player/Kwang/Kwang.h"
#include "Player/Shinbi/Shinbi.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Basic/BasicPC.h"
#include "ConstructorHelpers.h"
#include "Basic/BasicPC.h"
#include "Level/Stage/TriggerBox_CharacterSelect.h"

ABasicGM::ABasicGM()
{
	
}

void ABasicGM::PostLogin(APlayerController * NewPlayer)
{
	Super::PostLogin(NewPlayer);

	AllPlayer.Push(Cast<ABasicPC>(NewPlayer));
	AlivePlayer.Push(NewPlayer);

	if (AllPlayer.Num() == 4 && iWaitPlayerCnt == 4 && bIsCreateCharacterTrigger)
	{
		pCharacterSelectTrigger->StageStart();
	}

}

void ABasicGM::AddAlivePlayer(APlayerController * pPC)
{
	if (!pPC)
		return;

	AlivePlayer.Add(pPC);
}

void ABasicGM::RemoveAlivePlayer(APlayerController * pPC)
{
	if (!pPC)
		return;

	AlivePlayer.Remove(pPC);
}

void ABasicGM::WaitPlayerCreate()
{
	++iWaitPlayerCnt;

	UMyGameInstance * pGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!pGameInstance)
	{
		return;
	}

	if (iWaitPlayerCnt == 4 && bIsCreateCharacterTrigger && AllPlayer.Num() == 4)
	{
		pCharacterSelectTrigger->StageStart();
	}
}

void ABasicGM::CharacterTriggerCreate(ATriggerBox_CharacterSelect * CreateTrigger)
{
	bIsCreateCharacterTrigger = true;
	pCharacterSelectTrigger = CreateTrigger;


	UMyGameInstance * pGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!pGameInstance)
	{
		return;
	}

	if (iWaitPlayerCnt == 4 && AllPlayer.Num() == 4)
	{
		pCharacterSelectTrigger->StageStart();
	}
}

void ABasicGM::UpdateAllPlayerHP(float HP, FName CharacterName)
{
	for (int iCnt = 0; iCnt < AlivePlayer.Num(); ++iCnt)
	{
		ABasicPC * pPC = Cast<ABasicPC>(AlivePlayer[iCnt]);
		if (pPC)
		{
			pPC->UpdateAllPlayerHP(HP, CharacterName);
		}
	}
}

void ABasicGM::GameClear()
{
	for (int iCnt = 0; iCnt < AllPlayer.Num(); ++iCnt)
	{
		ABasicPC * pPC = Cast<ABasicPC>(AllPlayer[iCnt]);
		if (pPC)
		{
			pPC->SetClearUI();
		}
	}
}
