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

	//�̵��ӵ�
	//--------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Speed;
	//--------------------------------

	//����
	//--------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsJumping;
	//--------------------------------

	//ü��
	//--------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float CurrentHP;
	//--------------------------------

};
