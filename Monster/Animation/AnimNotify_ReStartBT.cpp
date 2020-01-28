// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_ReStartBT.h"
#include "Components/SkeletalMeshComponent.h"
#include "Monster/MonsterAIController.h"

void UAnimNotify_ReStartBT::Notify(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	if (!MeshComp->GetOwner()->GetWorld()->IsServer())
	{
		return;
	}

	APawn * pAPawn = Cast<APawn>(MeshComp->GetOwner());
	if (!pAPawn)
		return;


	AMonsterAIController * pAIController = Cast<AMonsterAIController>(pAPawn->GetController());
	if (!pAIController)
	{
		UE_LOG(LogClass, Warning, TEXT("ReStartAnim AIController false"));
		return;
	}

	pAIController->ReStartBT();
}
