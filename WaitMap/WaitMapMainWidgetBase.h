// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WaitMapMainWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UWaitMapMainWidgetBase : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	//캐릭터 선택 UI
	//------------------------------------------
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	UUserWidget * Choice;
	//------------------------------------------
};
