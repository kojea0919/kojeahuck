// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHPStateWidgetBase.h"
#include "Components/ProgressBar.h"

void UPlayerHPStateWidgetBase::NativeConstruct()
{
	ShinbiHPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("ShinbiHPBar")));
	KwangHPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("KwangHPBar")));
	GreystoneHPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("GreystoneHPBar")));
	CountessHPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("CountessHPBar")));


}

void UPlayerHPStateWidgetBase::SetShinbiHPPercent(float rate)
{
	ShinbiHPBar->SetPercent(rate);
}

void UPlayerHPStateWidgetBase::SetKwangHPPercent(float rate)
{
	KwangHPBar->SetPercent(rate);
}

void UPlayerHPStateWidgetBase::SetGreystoneHPPercent(float rate)
{
	GreystoneHPBar->SetPercent(rate);
}

void UPlayerHPStateWidgetBase::SetCountessHPPercent(float rate)
{
	CountessHPBar->SetPercent(rate);
}
