// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_ReStartBT.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UAnimNotify_ReStartBT : public UAnimNotify
{
	GENERATED_BODY()
public:
	//AIController를 통해서 멈춰있는 Behavior Tree를 다시 실행시킨다.
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
