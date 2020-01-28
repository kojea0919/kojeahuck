// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_ParticleOn.h"
#include "Components/SkeletalMeshComponent.h"
#include "Monster/Boss/Boss.h"

void UAnimNotify_ParticleOn::Notify(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	ABoss * pBoss = Cast<ABoss>(MeshComp->GetOwner());
	if (pBoss)
	{
		pBoss->SetPattern2Particle(true);
	}
}
