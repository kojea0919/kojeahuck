// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_ParticleOff.h"
#include "Components/SkeletalMeshComponent.h"
#include "Monster/Boss/Boss.h"

void UAnimNotify_ParticleOff::Notify(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	ABoss * pBoss = Cast<ABoss>(MeshComp->GetOwner());
	if (pBoss)
	{
		pBoss->SetPattern2Particle(false);
	}
}
