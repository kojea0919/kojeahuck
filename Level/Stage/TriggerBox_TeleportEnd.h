// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "TriggerBox_TeleportEnd.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API ATriggerBox_TeleportEnd : public ATriggerBox
{
	GENERATED_BODY()
public:
	ATriggerBox_TeleportEnd();

	virtual void BeginPlay() override;

	//TeleportEnd를 찾을 때 Key값을 비교해서 어떤
	//TeleportEndTrigger로 이동해야하는지 찾는다.
	//--------------------------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int iTriggerKey;
	//--------------------------------------------------


	//텔레포트 할 위치
	TArray<class ATeleportTargetPoint*> TeleportTargetPoints;

	//현재 텔레포트할 TeleportTargetpoints Idx
	int iCurTeleportIdx = 0;

	FVector GetTeleportLocation();


};
