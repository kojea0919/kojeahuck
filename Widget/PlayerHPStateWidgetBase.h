// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHPStateWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UPlayerHPStateWidgetBase : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UProgressBar * ShinbiHPBar;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UProgressBar * KwangHPBar;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UProgressBar * GreystoneHPBar;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UProgressBar * CountessHPBar;


	//각 체력바 setting함수
	//---------------------------------------
	void SetShinbiHPPercent(float rate);
	void SetKwangHPPercent(float rate);
	void SetGreystoneHPPercent(float rate);
	void SetCountessHPPercent(float rate);
	//---------------------------------------
};


