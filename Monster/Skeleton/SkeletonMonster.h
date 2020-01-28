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

	//발사체로 사용할 Blueprint가져오기
	//-----------------------------------------
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Projectile")
	TSubclassOf<class AMonsterProjectile> Projectile_Template;
	//-----------------------------------------

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

};