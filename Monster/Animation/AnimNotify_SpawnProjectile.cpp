// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_SpawnProjectile.h"
#include "Components/SkeletalMeshComponent.h"
#include "Monster/Skeleton/SkeletonMonster.h"
#include "Monster/Boss/Boss.h"

void UAnimNotify_SpawnProjectile::Notify(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	ASkeletonMonster * pSkeletonMonster = Cast<ASkeletonMonster>(MeshComp->GetOwner());
	if (pSkeletonMonster)
	{
		pSkeletonMonster->Shot();
		return;
	}

	ABoss * pBoss = Cast<ABoss>(MeshComp->GetOwner());
	if (pBoss)
	{
		pBoss->Shot();
		return;
	}
}
