// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerBox_TeleportEnd.h"
#include "Level/TeleportTargetPoint/TeleportTargetPoint.h"

ATriggerBox_TeleportEnd::ATriggerBox_TeleportEnd()
{

}

void ATriggerBox_TeleportEnd::BeginPlay()
{
	TArray<AActor*> TeleportPoints;

	//배치된 TeleportTargetPoint가져오기
	GetOverlappingActors(TeleportPoints, ATeleportTargetPoint::StaticClass());

	for (int iCnt = 0; iCnt < TeleportPoints.Num(); ++iCnt)
	{
		TeleportTargetPoints.Add(Cast< ATeleportTargetPoint>(TeleportPoints[iCnt]));
	}
}

FVector ATriggerBox_TeleportEnd::GetTeleportLocation()
{
	FVector TeleportLocation = TeleportTargetPoints[iCurTeleportIdx]->GetActorLocation();
	iCurTeleportIdx = (iCurTeleportIdx + 1) % TeleportTargetPoints.Num();
	return TeleportLocation;
}
