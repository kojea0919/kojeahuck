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

	//발사체로 사용할 Blueprint가져오기
	//-----------------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile")
	TSubclassOf<class AMonsterProjectile> Projectile_Template;
	//-----------------------------------------

	//Damage받았을 때 처리함수
	//-------------------------------------------
	virtual float TakeDamage(float Damage,
		struct FDamageEvent const& DamageEvent,
		AController* EventInstigator,
		AActor* DamageCauser) override;
	//-------------------------------------------

	//죽으면 현재 재생중인 Montage 정지
	//-------------------------------------------
	virtual void DeadProc() override;
	//-------------------------------------------

	//HP가 바뀌면 UI갱신
	//-------------------------------------------
	virtual void UpdateHPUI() override;
	//-------------------------------------------
	
	//Pattern2 에 대한 파티클 set함수
	//-------------------------------------------
	void SetPattern2Particle(bool bIsVisible);
	//-------------------------------------------

	//WeaponCollision을 On또는 Off시키는 함수
	//-------------------------------------------
	virtual void SetWeaponCollision(bool bCollisionOn);
	//-------------------------------------------

};
