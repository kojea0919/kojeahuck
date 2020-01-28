// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Monster/MonsterBase.h"
#include "MonsterAnim.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UMonsterAnim : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	//이동속도
	//--------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Speed;
	//--------------------------------

	//몬스터 상태
	//--------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EMonsterState MonsterState;
	//--------------------------------
};
