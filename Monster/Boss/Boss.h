// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monster/MonsterBase.h"
#include "Boss.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API ABoss : public AMonsterBase
{
	GENERATED_BODY()
public:
	ABoss();

	virtual void BeginPlay() override;

	//Components
	//-------------------------------------
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UBoxComponent * WeaponCollision;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UParticleSystemComponent * Pattern2Particle;
	//-------------------------------------
	//Components

	//Shot
	//-----------------------------------------
	void Shot();
	//-----------------------------------------

	//�߻�ü�� ����� Blueprint��������
	//-----------------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile")
	TSubclassOf<class AMonsterProjectile> Projectile_Template;
	//-----------------------------------------

	//Damage�޾��� �� ó���Լ�
	//-------------------------------------------
	virtual float TakeDamage(float Damage,
		struct FDamageEvent const& DamageEvent,
		AController* EventInstigator,
		AActor* DamageCauser) override;
	//-------------------------------------------

	//������ ���� ������� Montage ����
	//-------------------------------------------
	virtual void DeadProc() override;
	//-------------------------------------------

	//HP�� �ٲ�� UI����
	//-------------------------------------------
	virtual void UpdateHPUI() override;
	//-------------------------------------------
	
	//Pattern2 �� ���� ��ƼŬ set�Լ�
	//-------------------------------------------
	void SetPattern2Particle(bool bIsVisible);
	//-------------------------------------------

	//WeaponCollision�� On�Ǵ� Off��Ű�� �Լ�
	//-------------------------------------------
	virtual void SetWeaponCollision(bool bCollisionOn);
	//-------------------------------------------

};
