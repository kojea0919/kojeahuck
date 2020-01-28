// Fill out your copyright notice in the Description page of Project Settings.


#include "Greystone.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Monster/MonsterBase.h"

AGreystone::AGreystone()
{
	WeaponCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollision"));
	WeaponCollision->SetupAttachment(GetMesh(), TEXT("WeaponPosition"));
	WeaponCollision->SetRelativeLocation(FVector(0.0f, 0.0f, 74.0f));
	WeaponCollision->SetBoxExtent(FVector(7.0f, 7.0f, 58.0f));
	WeaponCollision->SetCollisionProfileName(TEXT("NoCollision"));
	WeaponCollision->OnComponentBeginOverlap.AddDynamic(this, &AGreystone::DoActorBeginOverlap);
}

void AGreystone::BeginPlay()
{
	Super::BeginPlay();
}

void AGreystone::SetWeaponCollision(bool bCollisionOn)
{
	if (bCollisionOn)
	{
		WeaponCollision->SetCollisionProfileName(TEXT("PlayerWeapon"));
	}
	else
	{
		WeaponCollision->SetCollisionProfileName(TEXT("NoCollision"));
	}
}
