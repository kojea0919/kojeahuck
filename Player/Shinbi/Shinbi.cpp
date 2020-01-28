// Fill out your copyright notice in the Description page of Project Settings.


#include "Shinbi.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Monster/MonsterBase.h"
#include "Kismet/GameplayStatics.h"
AShinbi::AShinbi()
{
	//Weapon 충돌 박스 설정
	//---------------------------------------
	WeaponCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollision"));
	WeaponCollision->SetupAttachment(GetMesh(), TEXT("weapon_r"));
	WeaponCollision->SetRelativeLocation(FVector(0.0f, -54.0f, 0.0f));
	WeaponCollision->SetRelativeRotation(FRotator(-7.0f, 0.0f, -90.0f));
	WeaponCollision->SetBoxExtent(FVector(7.0f, 7.0f, 43.0f));
	WeaponCollision->SetCollisionProfileName(TEXT("NoCollision"));
	WeaponCollision->OnComponentBeginOverlap.AddDynamic(this, &AShinbi::DoActorBeginOverlap);
	//---------------------------------------
}

void AShinbi::BeginPlay()
{
	Super::BeginPlay();
}

void AShinbi::SetWeaponCollision(bool bCollisionOn)
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
