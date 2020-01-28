// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_TeleportEnd.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Monster/Boss/Boss.h"
#include "GameFramework/CharacterMovementComponent.h"

void UAnimNotify_TeleportEnd::Notify(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	ABoss * pCurrentCharacter = Cast<ABoss>(MeshComp->GetOwner());
	if (pCurrentCharacter)
	{
		MeshComp->SetVisibility(true);
		
		pCurrentCharacter->GetCapsuleComponent()->SetCollisionProfileName(TEXT("Monster"));

		pCurrentCharacter->GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	}
}
