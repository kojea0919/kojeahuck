// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_SetTeleportState.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"


void UAnimNotify_SetTeleportState::Notify(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	ACharacter * pCurrentCharacter = Cast<ACharacter>(MeshComp->GetOwner());
	if (pCurrentCharacter)
	{
		//텔레포트 중에는 안 보이도록 설정
		MeshComp->SetVisibility(false);

		pCurrentCharacter->GetCapsuleComponent()->SetCollisionProfileName(TEXT("MonsterTeleportState"));

		//이동속도 높이기
		pCurrentCharacter->GetCharacterMovement()->MaxWalkSpeed = 10000.0f;
	}
}
