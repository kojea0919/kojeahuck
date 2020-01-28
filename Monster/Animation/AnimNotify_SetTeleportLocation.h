// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_SetTeleportLocation.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UAnimNotify_SetTeleportLocation : public UAnimNotify
{
	GENERATED_BODY()
public:
	//���Ͱ� �÷��̾� �ֺ����� Teleport������ ������ ã�´�.
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
