// Fill out your copyright notice in the Description page of Project Settings.


#include "WaitMapMainWidgetBase.h"

void UWaitMapMainWidgetBase::NativeConstruct()
{
	Choice = Cast<UUserWidget>(GetWidgetFromName(TEXT("UMG_choice")));
}
