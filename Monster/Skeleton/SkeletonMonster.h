// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monster/MonsterBase.h"
#include "SkeletonMonster.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API ASkeletonMonster : public AMonsterBase
{
	GENERATED_BODY()
	
public:
	ASkeletonMonster();

	//Shot
	//-----------------------------------------
	void Shot();
	//-----------------------------------------

	//�߻�ü�� ����� Blueprint��������
	//-----------------------------------------
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Projectile")
	TSubclassOf<class AMonsterProjectile> Projectile_Template;
	//-----------------------------------------

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

};