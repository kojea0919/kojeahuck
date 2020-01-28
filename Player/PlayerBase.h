// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerBase.generated.h"



//Player���°��� Enum
//----------------------------------------
UENUM(BlueprintType)
//Normal : �����̰ų� ������ �ִ� ����
//Attack : ���� ���� ����
enum class EPlayerState : uint8
{
	Normal = 0		UMETA(DisplayName = "Normal"),
	Attack = 1		UMETA(DisplayName = "Attack"),
	Dead = 2		UMETA(DisplayName = "Dead")
};
//----------------------------------------

UCLASS()
class PROJECT_API APlayerBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	//Components
	//--------------------------------------------------

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class USpringArmComponent * SpringArm;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UCameraComponent * Camera;
	//--------------------------------------------------



	//�Է¿� ���� ��������Ʈ �Լ�
	//--------------------------------------------------
	void MoveForward(float Value);
	void MoveRight(float Value);

	void PlayerJump();
	void PlayerJumpStop();
	void NormalAttack();
	//--------------------------------------------------


	//PlayerController�� ���� ȣ��� ���콺 �����ӿ� ���� �Լ�
	//-----------------------------------------------------------
	void ViewYaw(float Value);
	void ViewPitch(float Value);
	//-----------------------------------------------------------



	//�⺻ ���� ���� ��� ����
	//------------------------------------------------------------
	//���� ���� ���� �������� Ȯ���ϴ� ����
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Replicated)
	bool bIsAttackable = true;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	class UAnimMontage * NormalAttackMontage;
	//------------------------------------------------------------


	//Fade Out, Fade In
	//------------------------------------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class ULevelSequence * FadeOut;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class ULevelSequence * FadeIn;
	
	UFUNCTION(NetMulticast, Reliable)
	void S2A_PlayFadeIn();
	void S2A_PlayFadeIn_Implementation();

	UFUNCTION(NetMulticast, Reliable)
	void S2A_PlayFadeOut();
	void S2A_PlayFadeOut_Implementation();
	//------------------------------------------------------------


	//�÷��̾� ����
	//----------------------------------------------
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Replicated)
	EPlayerState CurPlayerState = EPlayerState::Normal;

	void SetPlayerState(EPlayerState NewState);

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, ReplicatedUsing = "OnRep_CurrentHP")
	float CurrentHP;

	void ReSetHP();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UAnimMontage * DeadMontage;
	//----------------------------------------------

	//������ ��ġ Set�Լ�
	//----------------------------------------------
	void SetRespawnLocation(FVector NewRespawnLocation);
	//----------------------------------------------

	//Respawn��ҷ� �̵���Ű�� �Լ�
	//----------------------------------------------
	void MoveToRespawn();
	//----------------------------------------------

	//HP�� �ٲ���� �� ȣ��� �Լ�
	//----------------------------------------------
	UFUNCTION()
	void OnRep_CurrentHP();

	void UpdateAllPlayerHPUI();
	//----------------------------------------------

	//Combo Set�Լ�
	//-----------------------------------------------
	void SetCurrentCombo(int iComboIdx);
	//-----------------------------------------------

	//�÷��̾� ���� Collision
	//-----------------------------------------------
	//AnimNotifyState_CheckOverlap���� ���ְ� ���ش�.
	virtual void SetWeaponCollision(bool bCollisionOn);
	//-----------------------------------------------

	//Damage�޾��� �� ó���Լ�
	//-------------------------------------------
	virtual float TakeDamage(float Damage,
		struct FDamageEvent const& DamageEvent,
		AController* EventInstigator,
		AActor* DamageCauser) override;
	//-------------------------------------------

	//Network Function
	//---------------------------------------------------
	UFUNCTION(Server,Reliable)
	void C2S_NormalAttack();
	void C2S_NormalAttack_Implementation();
	
	
	UFUNCTION(NetMulticast, Reliable)
	void S2A_NormalAttack();
	void S2A_NormalAttack_Implementation();


	UFUNCTION(NetMulticast, Reliable)
	void S2A_UpdateHPUI(float HP, FName CharacterName);
	void S2A_UpdateHPUI_Implementation(float HP, FName CharacterName);

	UFUNCTION(NetMulticast, Reliable)
	void S2A_Dead();
	void S2A_Dead_Implementation();
	//---------------------------------------------------
	//Network Function


	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
		void DoActorBeginOverlap(class UPrimitiveComponent * OverlappedComp,
			class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);
private:
	float MaxHP = 100;
	
	//���� �޺� ���¸� ��Ÿ���� ����
	int CurrentCombo = 0;

	//�ִ� �޺� ���� ��Ÿ���� ����
	int MaxCombo = 4;

	//�÷��̾� ������ ��ġ ����
	FVector RespawnLocation;
};