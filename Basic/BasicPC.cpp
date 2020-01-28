// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicPC.h"
#include "Player/PlayerBase.h"
#include "Widget/InGameMainBase.h"
#include "Widget/ClearWidgetBase.h"
#include "Basic/BasicGM.h"
#include "Kismet/GameplayStatics.h"



void ABasicPC::BeginPlay()
{
	//Local Player¸¸ ¼³Á¤
	if (IsLocalController())
	{
		bShowMouseCursor = true;
		bEnableClickEvents = true;

		SetInputMode(FInputModeGameAndUI());

		//Main UI Setting
		//--------------------------------------
		if (InGameMain_Template)
		{
			InGameMainUI = CreateWidget<UInGameMainBase>(this, InGameMain_Template);
			if (InGameMainUI)
			{
				InGameMainUI->AddToViewport();
			}
		}
		//--------------------------------------

		//Clear UI Setting
		//--------------------------------------
		if (Clear_Template)
		{
			ClearUI = CreateWidget<UClearWidgetBase>(this, Clear_Template);
		}
		//--------------------------------------
	}
}

void ABasicPC::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis(TEXT("Yaw"), this, &ABasicPC::ViewYaw);
	InputComponent->BindAxis(TEXT("Pitch"), this, &ABasicPC::ViewPitch);

	InputComponent->BindAction(TEXT("MouseRightClick"), IE_Pressed, this, &ABasicPC::CursorOff);
	InputComponent->BindAction(TEXT("MouseRightClick"), IE_Released, this, &ABasicPC::CursorOn);
}

void ABasicPC::CursorOff()
{
	bShowMouseCursor = false;
	PawnMouseInputOn();
}

void ABasicPC::CursorOn()
{
	bShowMouseCursor = true;
	PawnMouseInputOff();
}

void ABasicPC::ViewYaw(float Value)
{
	if (0 != Value && !bIsLockMouseMove)
	{
		APlayerBase * pPlayerBase = Cast<APlayerBase>(GetPawn());
		if (pPlayerBase)
		{
			pPlayerBase->ViewYaw(Value);
		}

		SetMouseLocation(CursorX, CursorY);
	}
}

void ABasicPC::ViewPitch(float Value)
{
	if (0 != Value && !bIsLockMouseMove)
	{
		APlayerBase * pPlayerBase = Cast<APlayerBase>(GetPawn());
		if (pPlayerBase)
		{
			pPlayerBase->ViewPitch(Value);
		}

		SetMouseLocation(CursorX, CursorY);
	}
}

void ABasicPC::PawnMouseInputOn()
{
	bIsLockMouseMove = false;
	GetMousePosition(CursorX, CursorY);
}

void ABasicPC::PawnMouseInputOff()
{
	bIsLockMouseMove = true;
	SetMouseLocation(CursorX, CursorY);
}

void ABasicPC::SetClearUI_Implementation()
{
	if (IsLocalController())
	{
		if (ClearUI)
		{
			ClearUI->AddToViewport();
		}
	}
}

void ABasicPC::UpdateBossHP(float Rate)
{
	if (IsLocalController())
	{
		if (InGameMainUI)
		{
			InGameMainUI->SetBossHPPercent(Rate);
		}
	}
}

void ABasicPC::UpdateBossUI()
{
	if (IsLocalController())
	{
		if (InGameMainUI)
		{
			InGameMainUI->SetVisibleBossUI(true);
		}
	}
}

void ABasicPC::UpdatePlayerHP(float Rate)
{
	if (IsLocalController())
	{
		if (InGameMainUI)
		{
			InGameMainUI->SetPlayerHPPercent(Rate);
		}
	}
}

void ABasicPC::UpdateAllPlayerHP_Implementation(float Rate, FName CharacterName)
{
	if (IsLocalController())
	{
		if (InGameMainUI)
		{
			if (CharacterName == TEXT("Shinbi"))
			{
				InGameMainUI->SetShinbiHPPercent(Rate);
			}

			else if (CharacterName == TEXT("Kwang"))
			{
				InGameMainUI->SetKwangHPPercent(Rate);
			}

			else if (CharacterName == TEXT("Greystone"))
			{
				InGameMainUI->SetGreystoneHPPercent(Rate);
			}

			else if (CharacterName == TEXT("Countess"))
			{
				InGameMainUI->SetCountessHPPercent(Rate);
			}
		}
	}
}


void ABasicPC::SetAllPlayerHPVisibility(bool bVisible)
{
	if (IsLocalController())
	{
		if (InGameMainUI)
		{
			InGameMainUI->SetVisibleAllPlayerHPUI(bVisible);
		}
	}
}

void ABasicPC::SetChoiceVisibility(bool bVisible)
{
	if (IsLocalController())
	{
		if (InGameMainUI)
		{
			InGameMainUI->SetVisibleChoiceUI(bVisible);
		}
	}
}

void ABasicPC::PossessToCharacter(APlayerBase * pTargetCharacter)
{
	if (pTargetCharacter)
	{
		Possess(pTargetCharacter);
	}
}