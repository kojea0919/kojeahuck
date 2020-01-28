// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_PlayerRespawn.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UAnimNotify_PlayerRespawn : public UAnimNotify
{
	GENERATED_BODY()

	//Á×Àº Player Respawn
	//----------------------------------------------------------------------------------
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);
	//----------------------------------------------------------------------------------
};
