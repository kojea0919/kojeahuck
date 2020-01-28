// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameMainBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UInGameMainBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UProgressBar * HPBar;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UProgressBar * BossHPBar;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UImage * BossImage;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UUserWidget * Choice;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UPlayerHPStateWidgetBase * AllPlayerHPBar;

	void SetBossHPPercent(float HPRate);

	void SetPlayerHPPercent(float HPRate);

	void SetShinbiHPPercent(float HPRate);
	void SetKwangHPPercent(float HPRate);
	void SetGreystoneHPPercent(float HPRate);
	void SetCountessHPPercent(float HPRate);

	void SetVisibleBossUI(bool bVisible);

	void SetVisibleChoiceUI(bool bVisible);

	void SetVisibleAllPlayerHPUI(bool bVisible);
};
