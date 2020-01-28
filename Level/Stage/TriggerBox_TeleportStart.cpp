// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerBox_TeleportStart.h"
#include "Kismet/GameplayStatics.h"
#include "Level/Stage/TriggerBox_TeleportEnd.h"
#include "Engine/World.h"
#include "Player/PlayerBase.h"

ATriggerBox_TeleportStart::ATriggerBox_TeleportStart()
{
	OnActorBeginOverlap.AddDynamic(this, &ATriggerBox_TeleportStart::OnOverlapBegin);
}


void ATriggerBox_TeleportStart::BeginPlay()
{
	TArray<AActor*> TeleportEndTrigger;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),
		ATriggerBox_TeleportEnd::StaticClass(),
		TeleportEndTrigger);

	//Key가 맞는 EndTrigger 찾기
	for(int iCnt = 0; iCnt < TeleportEndTrigger.Num(); ++iCnt)
	{
		ATriggerBox_TeleportEnd * pCurTrigger = Cast<ATriggerBox_TeleportEnd>(TeleportEndTrigger[iCnt]);
		if (pCurTrigger->iTriggerKey == iTriggerKey)
		{
			TeleportEnd = pCurTrigger;
			break;
		}
	}
}

void ATriggerBox_TeleportStart::OnOverlapBegin(AActor * OverlappedActor, AActor * OtherActor)
{
	APlayerBase * pOverlapPlayer = Cast<APlayerBase>(OtherActor);

	if (AlreadyTeleport.Find(pOverlapPlayer) >= 0)
	{
		return;
	}

	AlreadyTeleport.Push(Cast<APlayerBase>(OtherActor));

	if (GetWorld()->IsServer())
	{
		if (pOverlapPlayer)
		{
			FVector TeleportLocation = TeleportEnd->GetTeleportLocation();
			
			pOverlapPlayer->SetActorLocation(TeleportLocation);
			pOverlapPlayer->SetRespawnLocation(TeleportLocation);

			pOverlapPlayer->S2A_PlayFadeIn();
		}
	}
}
