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

	//TeleportEnd�� ã�� �� Key���� ���ؼ� �
	//TeleportEndTrigger�� �̵��ؾ��ϴ��� ã�´�.
	//--------------------------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int iTriggerKey;
	//--------------------------------------------------


	//�ڷ���Ʈ �� ��ġ
	TArray<class ATeleportTargetPoint*> TeleportTargetPoints;

	//���� �ڷ���Ʈ�� TeleportTargetpoints Idx
	int iCurTeleportIdx = 0;

	FVector GetTeleportLocation();


};
