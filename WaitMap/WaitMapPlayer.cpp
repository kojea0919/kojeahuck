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
	//Controller��������
	ABasicPC * pPC = Cast<ABasicPC>(GetController());


	if (pPC && !bIsSelectCharacter)
	{
		//ī�޶� ��ġ & ī�޶� �ٶ󺸴� ���� ���ϱ�
		FVector CameraLocation;
		FRotator CameraRotation;
		pPC->GetPlayerViewPoint(CameraLocation, CameraRotation);
		
		FVector TraceStart = CameraLocation;
		FVector TraceDirection = UKismetMathLibrary::GetForwardVector(CameraRotation);
		FVector TraceEnd = TraceStart + 500 * TraceDirection;

		//�浹 üũ�� ��ü ����
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

		//ī�޶� �ٶ󺸴� ���⿡ ĳ���Ͱ� ������ ���� UI ���̱�
		if (bResult) 
		{
			pPC->SetChoiceVisibility(true);
			bIsFocus = true;

			pTargetCharacter = Cast<APlayerBase>(OutHit.Actor);
		}
		//�����ٰ� �� ���̸� ���� UI ����
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
	//UI�� ����� �ִ� ��쿡�� ���� �����ϵ���
	if (bIsFocus)
	{
		ABasicPC * pPC = Cast<ABasicPC>(GetController());
		if (pPC)
		{
			//����â ���ֱ�
			pPC->SetChoiceVisibility(false);

			//��ü �÷��̾� ü�¹� ���̱�
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
		//��ġ�� �÷��̾ ����
		pPC->PossessToCharacter(pTargetCharacter);

		//Ʈ���ſ��� ĳ���� ���õ����� �˸���.
		pCharacterSelectTrigger->RemovePlayer(this);
		Destroy();
	}
}
