// Fill out your copyright notice in the Description page of Project Settings.


#include "Countess.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Monster/MonsterBase.h"
#include "Kismet/GameplayStatics.h"

ACountess::ACountess()
{
	LeftWeaponCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftWeaponCollision"));
	LeftWeaponCollision->SetupAttachment(GetMesh(), TEXT("weapon_r"));
	LeftWeaponCollision->SetRelativeLocation(FVector(0.0f, 0.0f, 74.0f));
	LeftWeaponCollision->SetBoxExtent(FVector(7.0f, 7.0f, 58.0f));
	LeftWeaponCollision->SetCollisionProfileName(TEXT("NoCollision"));
	LeftWeaponCollision->OnComponentBeginOverlap.AddDynamic(this, &ACountess::DoActorBeginOverlap);

	RightWeaponCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("RightWeaponCollision"));
	RightWeaponCollision->SetupAttachment(GetMesh(), TEXT("weapon_l"));
	RightWeaponCollision->SetRelativeLocation(FVector(0.0f, 0.0f, 74.0f));
	RightWeaponCollision->SetBoxExtent(FVector(7.0f, 7.0f, 58.0f));
	RightWeaponCollision->SetCollisionProfileName(TEXT("NoCollision"));
	RightWeaponCollision->OnComponentBeginOverlap.AddDynamic(this, &ACountess::DoActorBeginOverlap);
}

void ACountess::BeginPlay()
{
	Super::BeginPlay();
}

void ACountess::SetWeaponCollision(bool bCollisionOn)
{
	if (bCollisionOn)
	{
		LeftWeaponCollision->SetCollisionProfileName(TEXT("PlayerWeapon"));
		RightWeaponCollision->SetCollisionProfileName(TEXT("PlayerWeapon"));
	}
	else
	{
		LeftWeaponCollision->SetCollisionProfileName(TEXT("NoCollision"));
		RightWeaponCollision->SetCollisionProfileName(TEXT("NoCollision"));
	}
}
