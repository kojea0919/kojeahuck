// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/PlayerBase.h"
#include "WaitMapPlayer.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API AWaitMapPlayer : public APlayerBase
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	//캐릭터 선택 관련 변수
	//----------------------------------------------
	class ATriggerBox_CharacterSelect * pCharacterSelectTrigger;

	void SetCharacterSelectTrigger(ATriggerBox_CharacterSelect * pTrigger);
	//----------------------------------------------

	//선택한 캐릭터에 Possess와 기본 캐릭터 삭제
	//----------------------------------------------
	UFUNCTION(Server, Reliable)
	void C2S_RemoveWaitPlayer();
	void C2S_RemoveWaitPlayer_Implementation();
	//----------------------------------------------

private:
	FTimerHandle LookCharacterTimerHandle;

	//UI가 띄워져 있는지 나타내는 bool변수
	//---------------------------------------
	bool bIsFocus = false;
	//---------------------------------------

	//현재 보고있는 캐릭터
	//---------------------------------------
	APlayerBase * pTargetCharacter;
	//---------------------------------------

	//선택을 했는지
	//---------------------------------------
	bool bIsSelectCharacter = false;
	//---------------------------------------

	//현재 기본 캐릭터가 플레이어를 보고 있는지 
	//---------------------------------------
	void LookCharacter();
	//---------------------------------------

	//캐릭터 선택 함수
	//----------------------------------------------
	void SelectCharacter();
	//----------------------------------------------
};
