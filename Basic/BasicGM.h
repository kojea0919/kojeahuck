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



	//현재 연결된 플레이어 컨트롤러
	//----------------------------------------
	TArray<class ABasicPC*> AllPlayer;
	//----------------------------------------

	//현재 살아있는 플레이어 컨트롤러
	//----------------------------------------
	TArray<APlayerController*> AlivePlayer;

	void AddAlivePlayer(APlayerController * pPC);
	void RemoveAlivePlayer(APlayerController * pPC);
	//----------------------------------------

	//WaitPlayer가 생성되면 호출되고 iWaitPlayerCnt를 증가시킨다.
	//-----------------------------------------------------------
	void WaitPlayerCreate();
	//-----------------------------------------------------------

	//Trigger가 생성되면 호출되고 bIsCreateCharacterTrigger를 true로 바꾼다.
	//----------------------------------------------------------------------
	void CharacterTriggerCreate(class ATriggerBox_CharacterSelect * CreateTrigger);
	//----------------------------------------------------------------------


	//살아있는 모든 플레이어에게 HP 업데이트 하도록
	//----------------------------------------------------------------------
	void UpdateAllPlayerHP(float HP, FName CharacterName);
	//----------------------------------------------------------------------

	//게임 Clear UI
	//----------------------------------------------------------------------
	void GameClear();
	//----------------------------------------------------------------------
private:
	//현재 생성된 플레이어 숫자
	//----------------------------------------
	int iWaitPlayerCnt = 0;
	//----------------------------------------

	//캐릭터 선택 Trigger가 생성됐는지
	//----------------------------------------
	bool bIsCreateCharacterTrigger = false;
	//----------------------------------------

	class ATriggerBox_CharacterSelect * pCharacterSelectTrigger;
};
