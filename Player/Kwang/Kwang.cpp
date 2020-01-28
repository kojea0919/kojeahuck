// Fill out your copyright notice in the Description page of Project Settings.


#include "Kwang.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Monster/MonsterBase.h"

AKwang::AKwang()
{
	WeaponCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftWeaponCollision"));
	WeaponCollision->SetupAttachment(GetMesh(), TEXT("weapon_r"));
	WeaponCollision->SetRelativeLocation(FVector(0.0f, 0.0f, 74.0f));
	WeaponCollision->SetBoxExtent(FVector(7.0f, 7.0f, 58.0f));
	WeaponCollision->SetCollisionProfileName(TEXT("NoCollision"));
	WeaponCollision->OnComponentBeginOverlap.AddDynamic(this, &AKwang::DoActorBeginOverlap);
	
}


void AKwang::BeginPlay()
{
	Super::BeginPlay();
}

void AKwang::SetWeaponCollision(bool bCollisionOn)
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
