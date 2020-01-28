// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_ComboCheckEnd.h"
#include <Engine/World.h>
#include <Components/SkeletalMeshComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include "Player/PlayerBase.h"


void UAnimNotify_ComboCheckEnd::Notify(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	APlayerBase * pPlayer = Cast<APlayerBase>(MeshComp->GetOwner());
	if (pPlayer)
	{
		pPlayer->SetCurrentCombo(0);
		pPlayer->SetPlayerState(EPlayerState::Normal);
		pPlayer->GetCharacterMovement()->MaxWalkSpeed = 800.0f;
	}
}
