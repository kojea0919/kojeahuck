// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnim.h"
#include "Player/PlayerBase.h"
#include <GameFramework/CharacterMovementComponent.h>

void UPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	APlayerBase * pPlayer = Cast<APlayerBase>(TryGetPawnOwner());
	if (pPlayer)
	{
		//이동속도 가져오기
		//--------------------------------------------------------------
		Speed = pPlayer->GetCharacterMovement()->Velocity.Size2D();
		//--------------------------------------------------------------

		//점프 상태 가져오기
		//--------------------------------------------------------------
		bIsJumping = pPlayer->GetCharacterMovement()->IsFalling();
		//--------------------------------------------------------------

		//현재 체력 가져오기
		//--------------------------------------------------------------
		CurrentHP = pPlayer->CurrentHP;
		//--------------------------------------------------------------
	}

}
