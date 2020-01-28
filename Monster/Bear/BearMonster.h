// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monster/MonsterBase.h"
#include "BearMonster.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API ABearMonster : public AMonsterBase
{
	GENERATED_BODY()
	

public:
	ABearMonster();

	//Components
	//-------------------------------------
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UBoxComponent * LeftHandCollision;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UBoxComponent * RightHandCollision;
	//-------------------------------------
	//Components


	//Damage받았을 때 처리함수
	//-------------------------------------------
	virtual float TakeDamage(float Damage,
		struct FDamageEvent const& DamageEvent,
		AController* EventInstigator,
		AActor* DamageCauser) override;
	//-------------------------------------------

	//HP가 바뀌면 UI갱신
	//-------------------------------------------
	virtual void UpdateHPUI() override;
	//-------------------------------------------

	//Dead Proc 죽었을 때 처리할 것
	//-------------------------------------------
	float fDissolveAmount = 0;

	virtual void DeadProc() override;

	UFUNCTION()
	void Dissolve();

	void DissolveStart();
	//-------------------------------------------

	//WeaponCollision을 On또는 Off시키는 함수
	//-------------------------------------------
	virtual void SetWeaponCollision(bool bCollisionOn);
	//-------------------------------------------

	void PlayAttackMontage(FName AttackType);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
private:
	//디졸브 효과
	//-----------------------------
	float fMaxDissolveAmount = 5.6;
	
	FTimerHandle DissolveTimerHandler;
	//-----------------------------
};
