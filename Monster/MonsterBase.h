// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MonsterBase.generated.h"


//Monster상태관련 Enum
//----------------------------------------
UENUM(BlueprintType)
//Normal : 움직이거나 가만히 있는 상태
//Attack : 공격 중인 상태
enum class EMonsterState : uint8
{
	Normal = 0		UMETA(DisplayName = "Normal"),
	TargetOn = 1	UMETA(DisplayName = "TargetOn"),
	Attack = 2		UMETA(DisplayName = "Attack"),
	Dead = 3		UMETA(DisplayName = "Dead"),
	Teleport = 4	UMETA(DisplayName = "Teleport"),
	Pattern1 = 5	UMETA(DisplayName = "Pattern1"),
	Pattern2 = 6	UMETA(DisplayName = "Pattern2"),
	Pattern3 = 7	UMETA(DisplayName = "Pattern3")
};
//----------------------------------------

UCLASS()
class PROJECT_API AMonsterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMonsterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Component
	//-----------------------------------------
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UPawnSensingComponent* PawnSensing;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UWidgetComponent * HPBar;
	//-----------------------------------------
	//Component

	//몬스터 사거리
	//-------------------------------
	float AttackRange = 600.0f;
	float SkillAttackRange = 1200.0;
	//-------------------------------


	//몬스터 상태 관련 변수
	//-----------------------------------------
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	float MaxHP = 100;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, ReplicatedUsing = "OnRep_CurrentHP")
	float CurrentHP;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Replicated)
	EMonsterState MonsterState = EMonsterState::Normal;

	//몬스터가 현재 TargetOn돼있는 Player
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Replicated)
	class APlayerBase * TargetPlayer;

	//-----------------------------------------
	//몬스터 상태 관련 변수


	//SetState함수 : 현재 Monster상태 설정
	//---------------------------------
	void SetState(EMonsterState NewState);
	//---------------------------------

	//LookPlayer함수 : Player를 바라보도록 회전시키는 함수
	//-----------------------------------------------------
	void LookPlayer(float DeltaTime);
	//-----------------------------------------------------

	//HP가 바뀌면 불릴 함수
	//---------------------------------
	UFUNCTION()
	void OnRep_CurrentHP();

	virtual void UpdateHPUI();
	//---------------------------------


	//PawnSensing에서
	//플레이어를 발견했을 때 호출할 함수
	//-----------------------------------------
	UFUNCTION()
	void SeenPawn(APawn * Pawn);
	//-----------------------------------------

	//AI
	//-----------------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	class UBehaviorTree * MonsterBT;
	//-----------------------------------------

	//Damage를 받았을 때 사용할 파티클
	//-----------------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hit Effect")
	UParticleSystem * HitParticle;
	//-----------------------------------------

	//Damage를 받았을 때 사용할 파티클 생성함수
	//-----------------------------------------
	UFUNCTION(NetMulticast, Reliable)
	void S2A_SpawnHitParticle();
	void S2A_SpawnHitParticle_Implementation();
	//-----------------------------------------

	//Damage받았을 때 처리함수
	//-------------------------------------------
	virtual float TakeDamage(float Damage,
		struct FDamageEvent const& DamageEvent,
		AController* EventInstigator,
		AActor* DamageCauser) override;
	//-------------------------------------------

	//Dead Proc 죽었을 때 처리할 것
	//-------------------------------------------
	virtual void DeadProc();
	//-------------------------------------------

	//패턴 Montage가 재생중인지
	//------------------------------------------------------------
	void SetPlayingPattern(bool bNewPatternState);
	bool IsPlayingPattern();
	//------------------------------------------------------------

	//공격 패턴에 대한 Montage
	//------------------------------------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UAnimMontage * PatternMontage;
	//------------------------------------------------------------

	//공격 패턴 Montage 재생
	//------------------------------------------------------------
	UFUNCTION(NetMulticast, Reliable)
	void S2A_PlayPatternMontage(FName PatternName);
	void S2A_PlayPatternMontage_Implementation(FName PatternName);
	//------------------------------------------------------------

	//공격 패턴 Montage 정지
	//------------------------------------------------------------
	void StopPatternMontage();
	//------------------------------------------------------------


	//Weapon Overlap시 불릴 함수
	//-------------------------------------------
	UFUNCTION()
	void DoActorBeginOverlap(class UPrimitiveComponent * OverlappedComp,
		class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	virtual void SetWeaponCollision(bool bCollisionOn);
	//-------------------------------------------

	//Stage에서 현재 몬스터 수를 세고 있는데
	//몬스터가 죽은 경우 속해있는 Stage에 
	//삭제요청을 해야한다.
	//-------------------------------------------
	void AddStage(class ATriggerBox_Stage * pStage);

	class ATriggerBox_Stage * pCurrentStage;
	//-------------------------------------------


	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	//현재 Montage 재생중인지 판별하는 변수
	//------------------------------------------------------------
	bool bIsPlayingPattern = false;
	//------------------------------------------------------------
};
