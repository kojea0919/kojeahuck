// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_Destroy.h"
#include "Components/SkeletalMeshComponent.h"
#include "Monster/MonsterBase.h"


void UAnimNotify_Destroy::Notify(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	MeshComp->GetOwner()->Destroy();
}
