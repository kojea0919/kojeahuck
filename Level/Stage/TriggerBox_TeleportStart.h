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

	//TeleportEnd�� ã�� �� Key���� ���ؼ� �
	//TeleportEndTrigger�� �̵��ؾ��ϴ��� ã�´�.
	//--------------------------------------------------
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	int iTriggerKey;
	//--------------------------------------------------

	//�ڷ���Ʈ�� ��ġ�� �ִ� Ʈ����
	//--------------------------------------------------
	class ATriggerBox_TeleportEnd * TeleportEnd;//Stage ���� �Ǵ� Stage Clear�� ȣ��� �Լ�
	//--------------------------------------------------

	//�ڷ���Ʈ ������ �ش� �迭�� �ִ´�.
	TArray<class APlayerBase*> AlreadyTeleport;
};

