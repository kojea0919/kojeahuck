// Fill out your copyright notice in the Description page of Project Settings.


#include "SkeletonMonster.h"
#include "Engine/World.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Monster/MonsterProjectile.h"
#include "Player/PlayerBase.h"
#include "Widget/MonsterHPBarWidgetBase.h"
#include "Components/WidgetComponent.h"

ASkeletonMonster::ASkeletonMonster()
{
	AttackRange = 1200.0f;
}

void ASkeletonMonster::Shot()
{
	if (GetWorld()->IsServer())
	{
		FRotator LookPlayerRotator = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetPlayer->GetActorLocation());

		SetActorRotation(FRotator(0.0f, LookPlayerRotator.Yaw, 0.0f));

		FTransform ShotTransform = GetMesh()->GetSocketTransform(TEXT("ShotPosition"));

		AMonsterProjectile * pEnergy = GetWorld()->SpawnActor<AMonsterProjectile>(Projectile_Template,
			ShotTransform.GetLocation(),
			ShotTransform.GetRotation().Rotator());

		FVector Velocity = UKismetMathLibrary::Normal(TargetPlayer->GetActorLocation() - GetActorLocation()) * 700;

		if (pEnergy)
		{
			pEnergy->SetProjectVelocity(Velocity);
		}
	}
}

float ASkeletonMonster::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	return 0.0f;
}

void ASkeletonMonster::UpdateHPUI()
{
	//UI 업데이트
	UMonsterHPBarWidgetBase * pHPBar = Cast<UMonsterHPBarWidgetBase>(HPBar->GetUserWidgetObject());
	if (pHPBar)
	{
		pHPBar->SetHPRate(CurrentHP / MaxHP);
	}
}
