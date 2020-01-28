// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnim.h"
#include "Player/PlayerBase.h"
#include <GameFramework/CharacterMovementComponent.h>

void UPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	APlayerBase * pPlayer = Cast<APlayerBase>(TryGetPawnOwner());
	if (pPlayer)
	{
		//�̵��ӵ� ��������
		//--------------------------------------------------------------
		Speed = pPlayer->GetCharacterMovement()->Velocity.Size2D();
		//--------------------------------------------------------------

		//���� ���� ��������
		//--------------------------------------------------------------
		bIsJumping = pPlayer->GetCharacterMovement()->IsFalling();
		//--------------------------------------------------------------

		//���� ü�� ��������
		//--------------------------------------------------------------
		CurrentHP = pPlayer->CurrentHP;
		//--------------------------------------------------------------
	}

}
