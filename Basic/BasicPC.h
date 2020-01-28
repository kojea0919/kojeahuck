// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasicPC.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API ABasicPC : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;


	void SetupInputComponent();


	//입력에 대한 델리게이트 함수
	//--------------------------------------------------
	void CursorOff();
	void CursorOn();

	void ViewYaw(float Value);
	void ViewPitch(float Value);

	//--------------------------------------------------
	//입력에 대한 델리게이트 함수


	//Mouse움직임에 대한 입력은 CursorOff됐을 때
	//즉 마우스 오른쪽 버튼이 눌린 상황에만 받도록 한다.
	//--------------------------------------------------
	void PawnMouseInputOn();
	void PawnMouseInputOff();
	//--------------------------------------------------


	//마우스 움직임을 막아놓기 위한 변수
	//--------------------------------------
	bool bIsLockMouseMove = true;
	//--------------------------------------

	//마우스 위치를 저장하기 위한 변수
	//--------------------------------------
	float CursorX, CursorY;
	//--------------------------------------


	//MainUI
	//---------------------------------------
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UInGameMainBase * InGameMainUI;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "UI")
	TSubclassOf<class UInGameMainBase> InGameMain_Template;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UClearWidgetBase * ClearUI;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "UI")
	TSubclassOf<class UClearWidgetBase> Clear_Template;
	//---------------------------------------

	//보스 생성될 때 MainUI에서 체력바와 이미지 보이도록
	//----------------------------------------------------
	void UpdateBossHP(float Rate);
	void UpdateBossUI();
	//----------------------------------------------------

	//플레이어 체력 갱신
	//----------------------------------------------------
	
	//자기 자신 HPBar 갱신
	void UpdatePlayerHP(float Rate);

	//전체 Player HPBar 갱신
	UFUNCTION(NetMulticast,Reliable)
	void UpdateAllPlayerHP(float Rate, FName CharacterName);
	void UpdateAllPlayerHP_Implementation(float Rate,FName CharacterName);
	//----------------------------------------------------

	//Clear UI 띄우는 함수
	//----------------------------------
	UFUNCTION(NetMulticast, Reliable)
	void SetClearUI();
	void SetClearUI_Implementation();
	//----------------------------------




	void SetAllPlayerHPVisibility(bool bVisible);

	void SetChoiceVisibility(bool bVisible);

	//해당 Character에 Possess
	//--------------------------------------------------	
	void PossessToCharacter(class APlayerBase * pTargetCharacter);
	//--------------------------------------------------
};
