// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_SpawnProjectile.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UAnimNotify_SpawnProjectile : public UAnimNotify
{
	GENERATED_BODY()

	//NOtify�� �߻��� ������ �տ� Projectile��
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
