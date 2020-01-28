// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MonsterHPBarWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UMonsterHPBarWidgetBase : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UProgressBar * HPBar;

	//SetHPRateÇÔ¼ö
	//-----------------------------------
	void SetHPRate(float Rate);
	//-----------------------------------
};
