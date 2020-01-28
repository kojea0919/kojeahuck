// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_PatternEnd.h"
#include "Components/SkeletalMeshComponent.h"
#include "Monster/MonsterBase.h"
#include "Particles/ParticleSystemComponent.h"

void UAnimNotify_PatternEnd::Notify(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	AMonsterBase * pMonster = Cast<AMonsterBase>(MeshComp->GetOwner());
	if (pMonster)
	{
		pMonster->SetPlayingPattern(false);
	}
}
