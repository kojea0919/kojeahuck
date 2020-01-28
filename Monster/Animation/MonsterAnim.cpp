// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAnim.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMonsterAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	AMonsterBase * pMonster = Cast<AMonsterBase>(TryGetPawnOwner());
	if (pMonster)
	{
		//이동속도 가져오기
		//--------------------------------------------------------------
		Speed = pMonster->GetCharacterMovement()->Velocity.Size2D();
		//--------------------------------------------------------------

		//몬스터 상태 가져오기
		//--------------------------------------------------------------
		MonsterState = pMonster->MonsterState;
		//--------------------------------------------------------------
	}
}