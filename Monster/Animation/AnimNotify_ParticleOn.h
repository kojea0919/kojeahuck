// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_ParticleOn.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UAnimNotify_ParticleOn : public UAnimNotify
{
	GENERATED_BODY()
public:
	//보스 공격 Particle On
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
