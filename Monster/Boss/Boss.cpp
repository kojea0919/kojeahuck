// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Particles/ParticleSystemComponent.h"
#include "Monster/MonsterProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "Basic/BasicPC.h"
#include "Monster/MonsterAIController.h"

ABoss::ABoss()
{
	WeaponCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollision"));
	WeaponCollision->SetupAttachment(GetMesh(), TEXT("weapon_r"));
	WeaponCollision->SetCollisionProfileName(TEXT("NoCollision"));
	WeaponCollision->OnComponentBeginOverlap.AddDynamic(this, &ABoss::DoActorBeginOverlap);

	Pattern2Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Pattern2"));
	Pattern2Particle->bVisible = false;
	Pattern2Particle->SetupAttachment(GetMesh(), TEXT("Pattern2Base"));

	AttackRange = 300.0f;

	//보스 HPBar는 MainUI에서 띄운다.
	HPBar->SetVisibility(false);
}

void ABoss::BeginPlay()
{
	Super::BeginPlay();

	ABasicPC * pPlayerPC = Cast<ABasicPC>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (pPlayerPC)
	{
		pPlayerPC->UpdateBossUI();
	}
}

void ABoss::Shot()
{   
	//ShotPosition Transform
	FVector ShotBaseLocation = GetMesh()->GetSocketLocation(TEXT("Pattern2Base"));

	FRotator ShotRotation = GetActorRotation();

	//투사체 setting
	//---------------------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------------------
	AMonsterProjectile * pEnergy = GetWorld()->SpawnActor<AMonsterProjectile>(Projectile_Template,
		ShotBaseLocation,
		ShotRotation+FRotator(-5.0f,0.0f,0.0f));

	FVector Velocity = pEnergy->GetActorForwardVector() * 900;

	pEnergy->SetProjectVelocity(Velocity);

	for (int i = 1; i <= 5; ++i)
	{
		pEnergy = GetWorld()->SpawnActor<AMonsterProjectile>(Projectile_Template,
			ShotBaseLocation,
			ShotRotation + FRotator(-5.0f, i * 10, 0.0f));

		Velocity = pEnergy->GetActorForwardVector() * 900;

		pEnergy->SetProjectVelocity(Velocity);

		pEnergy = GetWorld()->SpawnActor<AMonsterProjectile>(Projectile_Template,
			ShotBaseLocation,
			ShotRotation + FRotator(-5.0f, -i * 10, 0.0f));

		Velocity = pEnergy->GetActorForwardVector() * 900;

		pEnergy->SetProjectVelocity(Velocity);
	}
	//---------------------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------------------
	//투사체 setting


	//Shot할 때 마다 가까이온 플레이어가 있는지 확인한다.
	//-------------------------------------------------
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel1));
	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(this);
	TArray<AActor*> OutActors;

	bool bResult = UKismetSystemLibrary::SphereOverlapActors(GetWorld(),
		GetActorLocation(),
		AttackRange,
		ObjectTypes,
		AActor::StaticClass(),
		IgnoreActors,
		OutActors);

	//있으면 근거리 공격으로 전환
	if (OutActors.Num() != 0)
	{
		bIsPlayingPattern = false;
		
		//Pattern2 파티클 끄기
		SetPattern2Particle(false);
		
		//애니메이션 멈추기
		StopAnimMontage(PatternMontage);

		//다시 거리에 따라서 어떤 공격을 할지 정한다.
		AMonsterAIController * pAI = Cast<AMonsterAIController>(GetController());
		if (pAI)
		{
			pAI->ReStartBT();
		}
	}
	//-------------------------------------------------
}

float ABoss::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	return 0.0f;
}

void ABoss::DeadProc()
{
	Super::DeadProc();

	StopAnimMontage(PatternMontage);
}

void ABoss::UpdateHPUI()
{
	ABasicPC * pPlayerPC = Cast<ABasicPC>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (pPlayerPC)
	{
		pPlayerPC->UpdateBossHP(CurrentHP / MaxHP);
	}
}

void ABoss::SetPattern2Particle(bool bIsVisible)
{
	Pattern2Particle->SetVisibility(bIsVisible);
}

void ABoss::SetWeaponCollision(bool bCollisionOn)
{
	if (bCollisionOn)
	{
		if(WeaponCollision)	
			WeaponCollision->SetCollisionProfileName(TEXT("MonsterWeapon"));
	}
	else
	{
		if (WeaponCollision)
			WeaponCollision->SetCollisionProfileName(TEXT("NoCollision"));
	}
}