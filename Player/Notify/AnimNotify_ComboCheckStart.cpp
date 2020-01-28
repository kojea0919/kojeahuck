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
		//CheckStart�� CheckEnd ���̿��� ���� �Է��� ������ ���� �޺��� �Ѿ� ������
		pPlayer->bIsAttackable = true;
	}
}
