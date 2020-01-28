// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_PatternStart.h"
#include "Monster/MonsterBase.h"
#include "Components/SkeletalMeshComponent.h"

void UAnimNotify_PatternStart::Notify(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	AMonsterBase * pMonster = Cast<AMonsterBase>(MeshComp->GetOwner());
	if (pMonster)
	{
		pMonster->SetPlayingPattern(true);
	}
}
