// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_ComboCheckEnd.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UAnimNotify_ComboCheckEnd : public UAnimNotify
{
	GENERATED_BODY()

	//처음 공격 모션으로 초기화
	//-------------------------------------------------------------------------------------------
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	//-------------------------------------------------------------------------------------------
};
