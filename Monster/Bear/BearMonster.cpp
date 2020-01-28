// Fill out your copyright notice in the Description page of Project Settings.


#include "BearMonster.h"
#include "Widget/MonsterHPBarWidgetBase.h"
#include "Components/WidgetComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"
#include "TimerManager.h"
#include "UnrealNetwork.h"

ABearMonster::ABearMonster()
{
	LeftHandCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftHand"));
	LeftHandCollision->SetupAttachment(GetMesh(), TEXT("hand_lf"));
	LeftHandCollision->SetCollisionProfileName(TEXT("NoCollision"));
	LeftHandCollision->OnComponentBeginOverlap.AddDynamic(this, &ABearMonster::DoActorBeginOverlap);

	RightHandCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("RightHand"));
	RightHandCollision->SetupAttachment(GetMesh(), TEXT("hand_rt"));
	RightHandCollision->SetCollisionProfileName(TEXT("NoCollision"));
	RightHandCollision->OnComponentBeginOverlap.AddDynamic(this, &ABearMonster::DoActorBeginOverlap);

	AttackRange = 300.0f;
	SkillAttackRange = 300.0f;
}

float ABearMonster::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	return 0.0f;
}

void ABearMonster::UpdateHPUI()
{
	//UI ������Ʈ
	UMonsterHPBarWidgetBase * pHPBar = Cast<UMonsterHPBarWidgetBase>(HPBar->GetUserWidgetObject());
	if (pHPBar)
	{
		pHPBar->SetHPRate(CurrentHP / MaxHP);
	}
}

void ABearMonster::DeadProc()
{
	Super::DeadProc();
}

void ABearMonster::Dissolve()
{
	//���� ��ü�� ������� �ʾ����� ���� ���� ����
	if (fDissolveAmount < fMaxDissolveAmount)
	{
		fDissolveAmount += 0.04;
		GetMesh()->SetScalarParameterValueOnMaterials(TEXT("Amount"), fDissolveAmount);
		
		GetWorldTimerManager().SetTimer(DissolveTimerHandler,
			this,
			&ABearMonster::Dissolve,
			0.01f,
			false);
	}
	//���Ϳ� ������ ȿ���� ���� ����Ǹ� Destroy
	else
	{
		GetWorldTimerManager().ClearTimer(DissolveTimerHandler);
		Destroy();
	}
}

void ABearMonster::DissolveStart()
{
	//Dissolveȿ��
	//-------------------------------------------------
	GetWorldTimerManager().SetTimer(DissolveTimerHandler,
		this,
		&ABearMonster::Dissolve,
		0.01f,
		false);
	//-------------------------------------------------
}

void ABearMonster::SetWeaponCollision(bool bCollisionOn)
{
	if (bCollisionOn)
	{
		LeftHandCollision->SetCollisionProfileName(TEXT("MonsterWeapon"));
		RightHandCollision->SetCollisionProfileName(TEXT("MonsterWeapon"));
	}
	else
	{
		LeftHandCollision->SetCollisionProfileName(TEXT("NoCollision"));
		RightHandCollision->SetCollisionProfileName(TEXT("NoCollision"));
	}
}

void ABearMonster::PlayAttackMontage(FName AttackType)
{
	PlayAnimMontage(PatternMontage, 1.0f, AttackType);
}

void ABearMonster::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}
