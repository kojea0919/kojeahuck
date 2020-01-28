// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterHPBarWidgetBase.h"
#include "Components/ProgressBar.h"

void UMonsterHPBarWidgetBase::NativeConstruct()
{
	HPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HP_Bar")));
}

void UMonsterHPBarWidgetBase::SetHPRate(float Rate)
{
	HPBar->SetPercent(Rate);
}
