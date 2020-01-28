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
		//충돌 체크할 물체 타입 설정
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel1));
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));

		//무시할 물체 설정
		TArray<AActor*> IgnoreActors;
		FVector TraceStart = pCurrentMonster->GetActorLocation();
		FVector TraceEnd = pCurrentMonster->TargetPlayer->GetActorLocation();

		//충돌한 물체와의 정보
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
