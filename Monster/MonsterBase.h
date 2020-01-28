// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MonsterBase.generated.h"


//Monster���°��� Enum
//----------------------------------------
UENUM(BlueprintType)
//Normal : �����̰ų� ������ �ִ� ����
//Attack : ���� ���� ����
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

	//���� ��Ÿ�
	//-------------------------------
	float AttackRange = 600.0f;
	float SkillAttackRange = 1200.0;
	//-------------------------------


	//���� ���� ���� ����
	//-----------------------------------------
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	float MaxHP = 100;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, ReplicatedUsing = "OnRep_CurrentHP")
	float CurrentHP;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Replicated)
	EMonsterState MonsterState = EMonsterState::Normal;

	//���Ͱ� ���� TargetOn���ִ� Player
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Replicated)
	class APlayerBase * TargetPlayer;

	//-----------------------------------------
	//���� ���� ���� ����


	//SetState�Լ� : ���� Monster���� ����
	//---------------------------------
	void SetState(EMonsterState NewState);
	//---------------------------------

	//LookPlayer�Լ� : Player�� �ٶ󺸵��� ȸ����Ű�� �Լ�
	//-----------------------------------------------------
	void LookPlayer(float DeltaTime);
	//-----------------------------------------------------

	//HP�� �ٲ�� �Ҹ� �Լ�
	//---------------------------------
	UFUNCTION()
	void OnRep_CurrentHP();

	virtual void UpdateHPUI();
	//---------------------------------


	//PawnSensing����
	//�÷��̾ �߰����� �� ȣ���� �Լ�
	//-----------------------------------------
	UFUNCTION()
	void SeenPawn(APawn * Pawn);
	//-----------------------------------------

	//AI
	//-----------------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	class UBehaviorTree * MonsterBT;
	//-----------------------------------------

	//Damage�� �޾��� �� ����� ��ƼŬ
	//-----------------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hit Effect")
	UParticleSystem * HitParticle;
	//-----------------------------------------

	//Damage�� �޾��� �� ����� ��ƼŬ �����Լ�
	//-----------------------------------------
	UFUNCTION(NetMulticast, Reliable)
	void S2A_SpawnHitParticle();
	void S2A_SpawnHitParticle_Implementation();
	//-----------------------------------------

	//Damage�޾��� �� ó���Լ�
	//-------------------------------------------
	virtual float TakeDamage(float Damage,
		struct FDamageEvent const& DamageEvent,
		AController* EventInstigator,
		AActor* DamageCauser) override;
	//-------------------------------------------

	//Dead Proc �׾��� �� ó���� ��
	//-------------------------------------------
	virtual void DeadProc();
	//-------------------------------------------

	//���� Montage�� ���������
	//------------------------------------------------------------
	void SetPlayingPattern(bool bNewPatternState);
	bool IsPlayingPattern();
	//------------------------------------------------------------

	//���� ���Ͽ� ���� Montage
	//------------------------------------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UAnimMontage * PatternMontage;
	//------------------------------------------------------------

	//���� ���� Montage ���
	//------------------------------------------------------------
	UFUNCTION(NetMulticast, Reliable)
	void S2A_PlayPatternMontage(FName PatternName);
	void S2A_PlayPatternMontage_Implementation(FName PatternName);
	//------------------------------------------------------------

	//���� ���� Montage ����
	//------------------------------------------------------------
	void StopPatternMontage();
	//------------------------------------------------------------


	//Weapon Overlap�� �Ҹ� �Լ�
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

	//Stage���� ���� ���� ���� ���� �ִµ�
	//���Ͱ� ���� ��� �����ִ� Stage�� 
	//������û�� �ؾ��Ѵ�.
	//-------------------------------------------
	void AddStage(class ATriggerBox_Stage * pStage);

	class ATriggerBox_Stage * pCurrentStage;
	//-------------------------------------------


	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	//���� Montage ��������� �Ǻ��ϴ� ����
	//------------------------------------------------------------
	bool bIsPlayingPattern = false;
	//------------------------------------------------------------
};
