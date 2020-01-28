// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_BearDissolve.h"
#include "Components/SkeletalMeshComponent.h"
#include "Monster/Bear/BearMonster.h"

void UAnimNotify_BearDissolve::Notify(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	ABearMonster * pBear = Cast<ABearMonster>(MeshComp->GetOwner());
	if (pBear)
	{
		pBear->DissolveStart();
	}
}
