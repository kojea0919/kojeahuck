// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnim.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UPlayerAnim : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	//이동속도
	//--------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Speed;
	//--------------------------------

	//점프
	//--------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsJumping;
	//--------------------------------

	//체력
	//--------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float CurrentHP;
	//--------------------------------

};
