// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState_MonsterOverlap.h"
#include "Components/SkeletalMeshComponent.h"
#include "Monster/MonsterBase.h"

void UAnimNotifyState_MonsterOverlap::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	if (MeshComp->GetOwner()->GetWorld()->IsServer())
	{
		AMonsterBase * pMonster = Cast<AMonsterBase>(MeshComp->GetOwner());
		if (pMonster)
		{
			//무기 충돌키기
			pMonster->SetWeaponCollision(true);
		}
	}
}

void UAnimNotifyState_MonsterOverlap::NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
}

void UAnimNotifyState_MonsterOverlap::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	if (MeshComp->GetOwner()->GetWorld()->IsServer())
	{
		AMonsterBase * pMonster = Cast<AMonsterBase>(MeshComp->GetOwner());
		if (pMonster)
		{
			//무기 충돌끄기
			pMonster->SetWeaponCollision(false);
		}
	}
}
