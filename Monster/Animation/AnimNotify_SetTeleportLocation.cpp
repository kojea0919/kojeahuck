// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_SetTeleportLocation.h"
#include "Engine/EngineTypes.h"
#include "Engine/World.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/Character.h" 
#include "Components/SkeletalMeshComponent.h"
#include "Monster/MonsterBase.h"
#include "Player/PlayerBase.h"

void UAnimNotify_SetTeleportLocation::Notify(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	AMonsterBase * pCurrentMonster = Cast<AMonsterBase>(MeshComp->GetOwner());


	if (pCurrentMonster)
	{
		//�浹 üũ�� ��ü Ÿ�� ����
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel1));
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));

		//������ ��ü ����
		TArray<AActor*> IgnoreActors;
		FVector TraceStart = pCurrentMonster->GetActorLocation();
		FVector TraceEnd = pCurrentMonster->TargetPlayer->GetActorLocation();

		//�浹�� ��ü���� ����
		FHitResult OutHit;

		bool IsResult = UKismetSystemLibrary::LineTraceSingleForObjects(
			pCurrentMonster->GetWorld(),
			TraceStart,
			TraceEnd,
			ObjectTypes,
			false,
			IgnoreActors,
			EDrawDebugTrace::ForDuration,
			OutHit,
			true,
			FLinearColor::Red,
			FLinearColor::Green,
			0.0f
		);

		
		if (IsResult)
		{

			UE_LOG(LogClass, Warning, TEXT("%s"), *OutHit.Actor->GetName());
		}
		else
		{
			UE_LOG(LogClass, Warning, TEXT("false"));
		}

	}
}
