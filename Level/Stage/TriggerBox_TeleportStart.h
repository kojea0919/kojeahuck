// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "TriggerBox_TeleportStart.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API ATriggerBox_TeleportStart : public ATriggerBox
{
	GENERATED_BODY()

public:
	ATriggerBox_TeleportStart();

	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnOverlapBegin(AActor * OverlappedActor, AActor * OtherActor);

	//TeleportEnd를 찾을 때 Key값을 비교해서 어떤
	//TeleportEndTrigger로 이동해야하는지 찾는다.
	//--------------------------------------------------
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	int iTriggerKey;
	//--------------------------------------------------

	//텔레포트할 위치가 있는 트리거
	//--------------------------------------------------
	class ATriggerBox_TeleportEnd * TeleportEnd;//Stage 시작 또는 Stage Clear시 호출될 함수
	//--------------------------------------------------

	//텔레포트 됐으면 해당 배열에 넣는다.
	TArray<class APlayerBase*> AlreadyTeleport;
};

