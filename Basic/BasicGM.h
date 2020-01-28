// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BasicGM.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API ABasicGM : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABasicGM();

	//void GoToTitle();
	virtual void PostLogin(APlayerController* NewPlayer) override;



	//���� ����� �÷��̾� ��Ʈ�ѷ�
	//----------------------------------------
	TArray<class ABasicPC*> AllPlayer;
	//----------------------------------------

	//���� ����ִ� �÷��̾� ��Ʈ�ѷ�
	//----------------------------------------
	TArray<APlayerController*> AlivePlayer;

	void AddAlivePlayer(APlayerController * pPC);
	void RemoveAlivePlayer(APlayerController * pPC);
	//----------------------------------------

	//WaitPlayer�� �����Ǹ� ȣ��ǰ� iWaitPlayerCnt�� ������Ų��.
	//-----------------------------------------------------------
	void WaitPlayerCreate();
	//-----------------------------------------------------------

	//Trigger�� �����Ǹ� ȣ��ǰ� bIsCreateCharacterTrigger�� true�� �ٲ۴�.
	//----------------------------------------------------------------------
	void CharacterTriggerCreate(class ATriggerBox_CharacterSelect * CreateTrigger);
	//----------------------------------------------------------------------


	//����ִ� ��� �÷��̾�� HP ������Ʈ �ϵ���
	//----------------------------------------------------------------------
	void UpdateAllPlayerHP(float HP, FName CharacterName);
	//----------------------------------------------------------------------

	//���� Clear UI
	//----------------------------------------------------------------------
	void GameClear();
	//----------------------------------------------------------------------
private:
	//���� ������ �÷��̾� ����
	//----------------------------------------
	int iWaitPlayerCnt = 0;
	//----------------------------------------

	//ĳ���� ���� Trigger�� �����ƴ���
	//----------------------------------------
	bool bIsCreateCharacterTrigger = false;
	//----------------------------------------

	class ATriggerBox_CharacterSelect * pCharacterSelectTrigger;
};
