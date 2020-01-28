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


	//Damage�޾��� �� ó���Լ�
	//-------------------------------------------
	virtual float TakeDamage(float Damage,
		struct FDamageEvent const& DamageEvent,
		AController* EventInstigator,
		AActor* DamageCauser) override;
	//-------------------------------------------

	//HP�� �ٲ�� UI����
	//-------------------------------------------
	virtual void UpdateHPUI() override;
	//-------------------------------------------

	//Dead Proc �׾��� �� ó���� ��
	//-------------------------------------------
	float fDissolveAmount = 0;

	virtual void DeadProc() override;

	UFUNCTION()
	void Dissolve();

	void DissolveStart();
	//-------------------------------------------

	//WeaponCollision�� On�Ǵ� Off��Ű�� �Լ�
	//-------------------------------------------
	virtual void SetWeaponCollision(bool bCollisionOn);
	//-------------------------------------------

	void PlayAttackMontage(FName AttackType);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
private:
	//������ ȿ��
	//-----------------------------
	float fMaxDissolveAmount = 5.6;
	
	FTimerHandle DissolveTimerHandler;
	//-----------------------------
};
