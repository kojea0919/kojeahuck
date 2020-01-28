// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerBase.generated.h"



//Player상태관련 Enum
//----------------------------------------
UENUM(BlueprintType)
//Normal : 움직이거나 가만히 있는 상태
//Attack : 공격 중인 상태
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



	//입력에 대한 델리게이트 함수
	//--------------------------------------------------
	void MoveForward(float Value);
	void MoveRight(float Value);

	void PlayerJump();
	void PlayerJumpStop();
	void NormalAttack();
	//--------------------------------------------------


	//PlayerController로 부터 호출될 마우스 움직임에 대한 함수
	//-----------------------------------------------------------
	void ViewYaw(float Value);
	void ViewPitch(float Value);
	//-----------------------------------------------------------



	//기본 공격 관련 멤버 변수
	//------------------------------------------------------------
	//현재 공격 가능 상태인지 확인하는 변수
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


	//플레이어 상태
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

	//리스폰 위치 Set함수
	//----------------------------------------------
	void SetRespawnLocation(FVector NewRespawnLocation);
	//----------------------------------------------

	//Respawn장소로 이동시키는 함수
	//----------------------------------------------
	void MoveToRespawn();
	//----------------------------------------------

	//HP가 바뀌었을 때 호출될 함수
	//----------------------------------------------
	UFUNCTION()
	void OnRep_CurrentHP();

	void UpdateAllPlayerHPUI();
	//----------------------------------------------

	//Combo Set함수
	//-----------------------------------------------
	void SetCurrentCombo(int iComboIdx);
	//-----------------------------------------------

	//플레이어 무기 Collision
	//-----------------------------------------------
	//AnimNotifyState_CheckOverlap에서 켜주고 꺼준다.
	virtual void SetWeaponCollision(bool bCollisionOn);
	//-----------------------------------------------

	//Damage받았을 때 처리함수
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
	
	//현재 콤보 상태를 나타내는 변수
	int CurrentCombo = 0;

	//최대 콤보 수를 나타내는 변수
	int MaxCombo = 4;

	//플레이어 리스폰 위치 변수
	FVector RespawnLocation;
};