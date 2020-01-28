// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_ComboCheckStart.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UAnimNotify_ComboCheckStart : public UAnimNotify
{
	GENERATED_BODY()

	//Start Notify�� �� �������� ����Ű�� �� �������� ���� ���� ���� �ִϸ��̼� ����
	//-------------------------------------------------------------------------------------------
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	//-------------------------------------------------------------------------------------------
};
