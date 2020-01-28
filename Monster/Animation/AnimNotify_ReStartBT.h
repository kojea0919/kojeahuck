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
	//AIController�� ���ؼ� �����ִ� Behavior Tree�� �ٽ� �����Ų��.
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
