// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MonsterProjectile.generated.h"

UCLASS()
class PROJECT_API AMonsterProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMonsterProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//Components
	//------------------------------------------
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UBoxComponent * BoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UParticleSystemComponent * ParticleSystem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UProjectileMovementComponent * ProjectileMovement;
	//------------------------------------------
	//Components

	//충돌시 사용할 파티클
	//-------------------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect")
	class UParticleSystem * HitParticle;
	//-------------------------------------------

	//Set
	//-------------------------------------------
	//속도 Setting해주는 함수
	void SetProjectVelocity(FVector & Velocity);
	//-------------------------------------------

	//Overlap시 불릴 함수
	//-------------------------------------------
	UFUNCTION()
		void DoActorBeginOverlap(class UPrimitiveComponent * OverlappedComp,
			class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

	UFUNCTION(NetMulticast,Reliable)
	void S2A_OverlapProc();
	void S2A_OverlapProc_Implementation();
	//-------------------------------------------
};
