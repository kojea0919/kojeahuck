// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/PlayerBase.h"
#include "Kwang.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API AKwang : public APlayerBase
{
	GENERATED_BODY()
public:
	AKwang();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	//Components
	//-------------------------------------------
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UBoxComponent * WeaponCollision;
	//-------------------------------------------
	//Components

	//Weapon Overlap시 불릴 함수
	//-------------------------------------------
	virtual void SetWeaponCollision(bool bCollisionOn) override;
	//-------------------------------------------
	//Overlap시 불릴 함수
};
