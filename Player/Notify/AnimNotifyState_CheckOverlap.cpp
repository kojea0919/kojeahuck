// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState_CheckOverlap.h"
#include "Components/SkeletalMeshComponent.h"
#include "Player/PlayerBase.h"

void UAnimNotifyState_CheckOverlap::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	
	if (MeshComp->GetOwner()->GetWorld()->IsServer())
	{
		APlayerBase * pPlayer = Cast<APlayerBase>(MeshComp->GetOwner());
		if (pPlayer)
		{
			//무기 충돌키기
			pPlayer->SetWeaponCollision(true);
		}
	}
}

void UAnimNotifyState_CheckOverlap::NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
}

void UAnimNotifyState_CheckOverlap::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	if (MeshComp->GetOwner()->GetWorld()->IsServer())
	{
		APlayerBase * pPlayer = Cast<APlayerBase>(MeshComp->GetOwner());
		if (pPlayer)
		{
			//무기 충돌끄기
			pPlayer->SetWeaponCollision(false);
		}
	}
}