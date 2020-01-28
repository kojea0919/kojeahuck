// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_PlayerRespawn.h"
#include <Engine/World.h>
#include <Components/SkeletalMeshComponent.h>
#include <Kismet/GameplayStatics.h>
#include <GameFramework/CharacterMovementComponent.h>
#include "Player/PlayerBase.h"
#include "Basic/BasicGM.h"

void UAnimNotify_PlayerRespawn::Notify(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	if (!MeshComp->GetOwner()->GetWorld()->IsServer())
		return;

	APlayerBase * pPlayer = Cast<APlayerBase>(MeshComp->GetOwner());
	if (pPlayer)
	{
		ABasicGM * pGM = Cast<ABasicGM>(UGameplayStatics::GetGameMode(pPlayer->GetWorld()));
		if (pGM)
		{
			pGM->AddAlivePlayer(Cast<APlayerController>(pPlayer->GetController()));
		}

		pPlayer->MoveToRespawn();
		pPlayer->ReSetHP();
		pPlayer->SetPlayerState(EPlayerState::Normal);
		pPlayer->bIsAttackable = true;
		pPlayer->GetCharacterMovement()->MaxWalkSpeed = 800.0f;
	}
}
