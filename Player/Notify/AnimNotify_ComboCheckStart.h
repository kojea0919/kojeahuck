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

	//Start Notify가 온 시점부터 공격키가 또 눌렸으면 다음 공격 동작 애니메이션 실행
	//-------------------------------------------------------------------------------------------
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	//-------------------------------------------------------------------------------------------
};
