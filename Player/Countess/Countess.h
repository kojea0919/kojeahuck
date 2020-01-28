// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/PlayerBase.h"
#include "Countess.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API ACountess : public APlayerBase
{
	GENERATED_BODY()
public:
	ACountess();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	//Components
	//-------------------------------------------
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UBoxComponent * LeftWeaponCollision;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UBoxComponent *RightWeaponCollision;
	//-------------------------------------------
	//Components

	//Weapon Overlap�� �Ҹ� �Լ�
	//-------------------------------------------
	virtual void SetWeaponCollision(bool bCollisionOn) override;
	//-------------------------------------------
	//Overlap�� �Ҹ� �Լ�

};
