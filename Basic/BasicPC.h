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


	//�Է¿� ���� ��������Ʈ �Լ�
	//--------------------------------------------------
	void CursorOff();
	void CursorOn();

	void ViewYaw(float Value);
	void ViewPitch(float Value);

	//--------------------------------------------------
	//�Է¿� ���� ��������Ʈ �Լ�


	//Mouse�����ӿ� ���� �Է��� CursorOff���� ��
	//�� ���콺 ������ ��ư�� ���� ��Ȳ���� �޵��� �Ѵ�.
	//--------------------------------------------------
	void PawnMouseInputOn();
	void PawnMouseInputOff();
	//--------------------------------------------------


	//���콺 �������� ���Ƴ��� ���� ����
	//--------------------------------------
	bool bIsLockMouseMove = true;
	//--------------------------------------

	//���콺 ��ġ�� �����ϱ� ���� ����
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

	//���� ������ �� MainUI���� ü�¹ٿ� �̹��� ���̵���
	//----------------------------------------------------
	void UpdateBossHP(float Rate);
	void UpdateBossUI();
	//----------------------------------------------------

	//�÷��̾� ü�� ����
	//----------------------------------------------------
	
	//�ڱ� �ڽ� HPBar ����
	void UpdatePlayerHP(float Rate);

	//��ü Player HPBar ����
	UFUNCTION(NetMulticast,Reliable)
	void UpdateAllPlayerHP(float Rate, FName CharacterName);
	void UpdateAllPlayerHP_Implementation(float Rate,FName CharacterName);
	//----------------------------------------------------

	//Clear UI ���� �Լ�
	//----------------------------------
	UFUNCTION(NetMulticast, Reliable)
	void SetClearUI();
	void SetClearUI_Implementation();
	//----------------------------------




	void SetAllPlayerHPVisibility(bool bVisible);

	void SetChoiceVisibility(bool bVisible);

	//�ش� Character�� Possess
	//--------------------------------------------------	
	void PossessToCharacter(class APlayerBase * pTargetCharacter);
	//--------------------------------------------------
};
