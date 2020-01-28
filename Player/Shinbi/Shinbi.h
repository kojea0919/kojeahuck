// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/PlayerBase.h"
#include "Shinbi.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API AShinbi : public APlayerBase
{
	GENERATED_BODY()
public:
	AShinbi();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;




	//Components
	//-------------------------------------------
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UBoxComponent * WeaponCollision;
	//-------------------------------------------
	//Components



	//Weapon Overlap�� �Ҹ� �Լ�
	//-------------------------------------------
	virtual void SetWeaponCollision(bool bCollisionOn) override;
	//-------------------------------------------
	//Overlap�� �Ҹ� �Լ�

};
