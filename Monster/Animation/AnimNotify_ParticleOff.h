// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_ParticleOff.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UAnimNotify_ParticleOff : public UAnimNotify
{
	GENERATED_BODY()
public:
	//���� ���� Particle Off
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
