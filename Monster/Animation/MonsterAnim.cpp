// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAnim.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMonsterAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	AMonsterBase * pMonster = Cast<AMonsterBase>(TryGetPawnOwner());
	if (pMonster)
	{
		//�̵��ӵ� ��������
		//--------------------------------------------------------------
		Speed = pMonster->GetCharacterMovement()->Velocity.Size2D();
		//--------------------------------------------------------------

		//���� ���� ��������
		//--------------------------------------------------------------
		MonsterState = pMonster->MonsterState;
		//--------------------------------------------------------------
	}
}