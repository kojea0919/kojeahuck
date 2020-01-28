// Fill out your copyright notice in the Description page of Project Settings.


#include "WaitMapPlayer.h"
#include "TimerManager.h"
#include "Basic/BasicPC.h"
#include "Basic/BasicGM.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"
#include "Level/Stage/TriggerBox_CharacterSelect.h"
#include "Kismet/GameplayStatics.h"
#include "UnrealNetwork.h"
#include "Basic/MyGameInstance.h"

void AWaitMapPlayer::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(LookCharacterTimerHandle,
		this,
		&AWaitMapPlayer::LookCharacter,
		0.1f,
		true);

	ABasicGM * pGM = Cast<ABasicGM>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!pGM)
		return;

	pGM->WaitPlayerCreate();


}

void AWaitMapPlayer::SetupPlayerInputComponent(UInputComponent * PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Possess"), IE_Pressed, this, &AWaitMapPlayer::SelectCharacter);
}

void AWaitMapPlayer::LookCharacter()
{
	//Controller가져오기
	ABasicPC * pPC = Cast<ABasicPC>(GetController());


	if (pPC && !bIsSelectCharacter)
	{
		//카메라 위치 & 카메라가 바라보는 방향 구하기
		FVector CameraLocation;
		FRotator CameraRotation;
		pPC->GetPlayerViewPoint(CameraLocation, CameraRotation);
		
		FVector TraceStart = CameraLocation;
		FVector TraceDirection = UKismetMathLibrary::GetForwardVector(CameraRotation);
		FVector TraceEnd = TraceStart + 500 * TraceDirection;

		//충돌 체크할 물체 선택
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel1));

		TArray<AActor*> IgnoreActors;

		FHitResult OutHit;

		bool bResult = UKismetSystemLibrary::LineTraceSingleForObjects(
			GetWorld(),
			TraceStart,
			TraceEnd,
			ObjectTypes,
			false,
			IgnoreActors,
			EDrawDebugTrace::None,
			OutHit,
			true,
			FLinearColor::Red,
			FLinearColor::Green,
			5.0f
		);

		//카메라가 바라보는 방향에 캐릭터가 있으면 선택 UI 보이기
		if (bResult) 
		{
			pPC->SetChoiceVisibility(true);
			bIsFocus = true;

			pTargetCharacter = Cast<APlayerBase>(OutHit.Actor);
		}
		//보였다가 안 보이면 선택 UI 제거
		else if(bIsFocus)
		{
			pPC->SetChoiceVisibility(false);
			bIsFocus = false;
		}
	}
	
	else if(bIsSelectCharacter)
	{
		pPC->SetChoiceVisibility(false);
	}
}

void AWaitMapPlayer::SetCharacterSelectTrigger(ATriggerBox_CharacterSelect * pTrigger)
{
	if (pTrigger)
		pCharacterSelectTrigger = pTrigger;
}

void AWaitMapPlayer::SelectCharacter()
{
	//UI가 띄워져 있는 경우에만 선택 가능하도록
	if (bIsFocus)
	{
		ABasicPC * pPC = Cast<ABasicPC>(GetController());
		if (pPC)
		{
			//선택창 없애기
			pPC->SetChoiceVisibility(false);

			//전체 플레이어 체력바 보이기
			pPC->SetAllPlayerHPVisibility(true);


			bIsSelectCharacter = true;
		}
		C2S_RemoveWaitPlayer();
	}
}

void AWaitMapPlayer::C2S_RemoveWaitPlayer_Implementation()
{
	ABasicPC * pPC = Cast<ABasicPC>(GetController());
	if (pPC)
	{
		//배치된 플레이어에 빙의
		pPC->PossessToCharacter(pTargetCharacter);

		//트리거에게 캐릭터 선택됐음을 알린다.
		pCharacterSelectTrigger->RemovePlayer(this);
		Destroy();
	}
}
