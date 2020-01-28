// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameMainBase.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "Widget/PlayerHPStateWidgetBase.h"

void UInGameMainBase::NativeConstruct()
{
	HPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HP_Bar")));
	
	BossHPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("BossHPBar")));

	BossImage = Cast<UImage>(GetWidgetFromName(TEXT("BossImage")));

	Choice = Cast<UUserWidget>(GetWidgetFromName(TEXT("Choice")));

	AllPlayerHPBar = Cast<UPlayerHPStateWidgetBase>(GetWidgetFromName(TEXT("PlayerHPState")));

	Choice->SetVisibility(ESlateVisibility::Hidden);
	BossHPBar->SetVisibility(ESlateVisibility::Hidden);
	BossImage->SetVisibility(ESlateVisibility::Hidden);
	AllPlayerHPBar->SetVisibility(ESlateVisibility::Hidden);

	SetBossHPPercent(1);
}

void UInGameMainBase::SetBossHPPercent(float HPRate = 1.0f)
{
	if(BossHPBar)
		BossHPBar->SetPercent(HPRate);
}

void UInGameMainBase::SetPlayerHPPercent(float HPRate)
{
	if(HPBar)
		HPBar->SetPercent(HPRate);
}

void UInGameMainBase::SetShinbiHPPercent(float HPRate)
{
	if (AllPlayerHPBar)
	{
		AllPlayerHPBar->SetShinbiHPPercent(HPRate);
	}
}

void UInGameMainBase::SetKwangHPPercent(float HPRate)
{
	if (AllPlayerHPBar)
	{
		AllPlayerHPBar->SetKwangHPPercent(HPRate);
	}
}

void UInGameMainBase::SetGreystoneHPPercent(float HPRate)
{
	if (AllPlayerHPBar)
	{
		AllPlayerHPBar->SetGreystoneHPPercent(HPRate);
	}
}

void UInGameMainBase::SetCountessHPPercent(float HPRate)
{
	if (AllPlayerHPBar)
	{

		AllPlayerHPBar->SetCountessHPPercent(HPRate);
	}
}

void UInGameMainBase::SetVisibleBossUI(bool bVisible)
{
	if (bVisible)
	{
		BossHPBar->SetVisibility(ESlateVisibility::Visible);
		BossImage->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		BossHPBar->SetVisibility(ESlateVisibility::Hidden);
		BossImage->SetVisibility(ESlateVisibility::Hidden);
	}

}

void UInGameMainBase::SetVisibleChoiceUI(bool bVisible)
{
	if (bVisible)
	{
		Choice->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		Choice->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UInGameMainBase::SetVisibleAllPlayerHPUI(bool bVisible)
{
	if (bVisible)
	{
		AllPlayerHPBar->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		AllPlayerHPBar->SetVisibility(ESlateVisibility::Hidden);
	}
}

