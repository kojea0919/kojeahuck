// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_ComboCheckStart.h"
#include <Engine/World.h>
#include <Components/SkeletalMeshComponent.h>
#include "Player/PlayerBase.h"

void UAnimNotify_ComboCheckStart::Notify(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	APlayerBase * pPlayer = Cast<APlayerBase>(MeshComp->GetOwner());
	if (pPlayer)
	{
		//CheckStart와 CheckEnd 사이에서 공격 입력을 받으면 다음 콤보로 넘어 가도록
		pPlayer->bIsAttackable = true;
	}
}
