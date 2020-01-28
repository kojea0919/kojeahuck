// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterProjectile.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Player/PlayerBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMonsterProjectile::AMonsterProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//UParticleSystem 설정
	//------------------------------------------------------------------------------------
	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	RootComponent = ParticleSystem;
	//------------------------------------------------------------------------------------

	//Box Collision 설정
	//------------------------------------------
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	BoxComponent->SetupAttachment(ParticleSystem);
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AMonsterProjectile::DoActorBeginOverlap);

	//------------------------------------------

	//ProjectileMovement 설정
	//------------------------------------------------------------------------------------
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	//------------------------------------------------------------------------------------
}

// Called when the game starts or when spawned
void AMonsterProjectile::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(5.0f);
}

// Called every frame
void AMonsterProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMonsterProjectile::SetProjectVelocity(FVector & Velocity)
{
	ProjectileMovement->Velocity = Velocity;
}

void AMonsterProjectile::DoActorBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (GetWorld()->IsServer())
	{
		APlayerBase * pPlayer = Cast<APlayerBase>(OtherActor);
		if (pPlayer)
		{
			UGameplayStatics::ApplyDamage(pPlayer, 5.0f, nullptr, this, NULL);
		}

		//맞았을 때 Particle생성
		S2A_OverlapProc();
		Destroy();
	}
}


void AMonsterProjectile::S2A_OverlapProc_Implementation()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, GetActorTransform());
}
