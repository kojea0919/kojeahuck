// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_ScopeAttack.h"
#include "Components/SkeletalMeshComponent.h"
#include "Player/PlayerBase.h"
#include "Kismet/GameplayStatics.h"

void UAnimNotify_ScopeAttack::Notify(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	APlayerBase * pPlayer = Cast<APlayerBase>(MeshComp->GetOwner());
	if (pPlayer)
	{
		TArray<AActor*> IgnoreActor;
		IgnoreActor.Add(pPlayer);

		//주위에게 데미지 주기
		UGameplayStatics::ApplyRadialDamage(pPlayer->GetWorld(),
			40.0f, pPlayer->GetActorLocation(), 200.0f,
			NULL, IgnoreActor, pPlayer, pPlayer->GetController());
	}
}
