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


	//ĳ���� ���� ���� ����
	//----------------------------------------------
	class ATriggerBox_CharacterSelect * pCharacterSelectTrigger;

	void SetCharacterSelectTrigger(ATriggerBox_CharacterSelect * pTrigger);
	//----------------------------------------------

	//������ ĳ���Ϳ� Possess�� �⺻ ĳ���� ����
	//----------------------------------------------
	UFUNCTION(Server, Reliable)
	void C2S_RemoveWaitPlayer();
	void C2S_RemoveWaitPlayer_Implementation();
	//----------------------------------------------

private:
	FTimerHandle LookCharacterTimerHandle;

	//UI�� ����� �ִ��� ��Ÿ���� bool����
	//---------------------------------------
	bool bIsFocus = false;
	//---------------------------------------

	//���� �����ִ� ĳ����
	//---------------------------------------
	APlayerBase * pTargetCharacter;
	//---------------------------------------

	//������ �ߴ���
	//---------------------------------------
	bool bIsSelectCharacter = false;
	//---------------------------------------

	//���� �⺻ ĳ���Ͱ� �÷��̾ ���� �ִ��� 
	//---------------------------------------
	void LookCharacter();
	//---------------------------------------

	//ĳ���� ���� �Լ�
	//----------------------------------------------
	void SelectCharacter();
	//----------------------------------------------
};
