#include "Player/PlayerBase.h"
#include <Components/CapsuleComponent.h>
#include <Components/BoxComponent.h>
#include <Components/SkeletalMeshComponent.h>
#include <Components/InputComponent.h>
#include <Components/CapsuleComponent.h>
#include <Camera/CameraComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <Kismet/KismetMathLibrary.h>
#include "Kismet/GameplayStatics.h"
#include "Monster/MonsterBase.h"
#include "UnrealNetwork.h"
#include "Basic/BasicPC.h"
#include "Player/Countess/Countess.h"
#include "Player/Greystone/Greystone.h"
#include "Player/Kwang/Kwang.h"
#include "Player/Shinbi/Shinbi.h"
#include "Basic/BasicGM.h"
#include "LevelSequence/Public/LevelSequencePlayer.h"
#include "MovieScene/Public/MovieSceneSequencePlayer.h"

// Sets default values
APlayerBase::APlayerBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Capsule설정
	//---------------------------------------
	GetCapsuleComponent()->SetCapsuleHalfHeight(120.0f);
	//---------------------------------------

	//Skeletal Mesh 초기 설정
	//---------------------------------------
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -120.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetWorldScale3D(FVector(1.3f, 1.3f, 1.3f));
	//---------------------------------------

	//SpringArm 초기 설정
	//---------------------------------------
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetMesh());
	SpringArm->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 130.0f));
	SpringArm->bUsePawnControlRotation = true;
	//---------------------------------------

	//Camera 초기 설정
	//---------------------------------------
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	//---------------------------------------

	//CharacterMovement 초기 설정
	//---------------------------------------
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 800.0f;
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	//---------------------------------------
}

// Called when the game starts or when spawned
void APlayerBase::BeginPlay()
{
	Super::BeginPlay();

	//마우스 회전은 카메라만 움직이도록 하자
	bUseControllerRotationYaw = false;
	
	CurrentHP = MaxHP;
}

// Called every frame
void APlayerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerBase::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &APlayerBase::MoveRight);

	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &APlayerBase::PlayerJump);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Released, this, &APlayerBase::PlayerJumpStop);

	PlayerInputComponent->BindAction(TEXT("NormalAttack"), IE_Pressed, this, &APlayerBase::NormalAttack);
}

void APlayerBase::MoveForward(float Value)
{
	//0이 아니고 플레이어가 살아있는 경우 움직인다.
	if (0 != Value && CurPlayerState != EPlayerState::Dead)
	{
		if (CurPlayerState == EPlayerState::Attack)
		{	
			GetCharacterMovement()->MaxWalkSpeed = 400.0f;
		}
		AddMovementInput(UKismetMathLibrary::GetForwardVector(FRotator(0.0f, GetControlRotation().Yaw, 0.0f)), Value);
	}
}

void APlayerBase::MoveRight(float Value)
{
	//0이 아니고 플레이어가 살아있는 경우 움직인다.
	if (0 != Value && CurPlayerState != EPlayerState::Dead)
	{
		if (CurPlayerState == EPlayerState::Attack)
		{
			GetCharacterMovement()->MaxWalkSpeed = 400.0f;
		}
		AddMovementInput(UKismetMathLibrary::GetRightVector(FRotator(0.0f, GetControlRotation().Yaw, 0.0f)), Value);
	}
}

void APlayerBase::PlayerJump()
{
	Jump();
}

void APlayerBase::PlayerJumpStop()
{
	StopJumping();
}

void APlayerBase::NormalAttack()
{
	//공격이 가능한 상황인지 판별
	if (bIsAttackable && NormalAttackMontage && CurPlayerState != EPlayerState::Dead)
	{
		C2S_NormalAttack();
	}
}



void APlayerBase::ViewYaw(float Value)
{
	AddControllerYawInput(Value);
}

void APlayerBase::ViewPitch(float Value)
{
	AddControllerPitchInput(Value);
}

void APlayerBase::S2A_PlayFadeIn_Implementation()
{
	//내 플레이어만 FadeIn 효과
	if (IsLocallyControlled())
	{
		ALevelSequenceActor * Temp;

		ULevelSequencePlayer * FadeInPlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(),
			FadeIn, FMovieSceneSequencePlaybackSettings(), Temp);

		if(FadeInPlayer)
			FadeInPlayer->Play();

	}
}

void APlayerBase::S2A_PlayFadeOut_Implementation()
{
	//내 플레이어만 FadeIn 효과
	if (IsLocallyControlled())
	{
		ALevelSequenceActor * Temp;

		ULevelSequencePlayer * FadeOutPlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(),
			FadeOut, FMovieSceneSequencePlaybackSettings(), Temp);

		if (FadeOutPlayer)
			FadeOutPlayer->Play();
	}
}

void APlayerBase::SetPlayerState(EPlayerState NewState)
{
	CurPlayerState = NewState;
}

void APlayerBase::ReSetHP()
{
	CurrentHP = 100.0f;
	OnRep_CurrentHP();
	UpdateAllPlayerHPUI();
}

void APlayerBase::SetRespawnLocation(FVector NewRespawnLocation)
{
	RespawnLocation = NewRespawnLocation;
}


void APlayerBase::MoveToRespawn()
{
	SetActorLocation(RespawnLocation);
}

void APlayerBase::OnRep_CurrentHP()
{
	ABasicPC * pPC = Cast<ABasicPC>(GetController());
	if (pPC)
	{
		pPC->UpdatePlayerHP(CurrentHP / MaxHP);
	}
}

void APlayerBase::UpdateAllPlayerHPUI()
{
	ABasicGM * pGM = Cast<ABasicGM>(UGameplayStatics::GetGameMode(GetWorld()));
	
	if (!pGM)
		return;

	if (Cast<AShinbi>(this))
	{
		pGM->UpdateAllPlayerHP(CurrentHP / MaxHP, TEXT("Shinbi"));
	}
	else if (Cast<AKwang>(this))
	{
		pGM->UpdateAllPlayerHP(CurrentHP / MaxHP, TEXT("Kwang"));
	}
	else if (Cast<AGreystone>(this))
	{
		pGM->UpdateAllPlayerHP(CurrentHP / MaxHP, TEXT("Greystone"));
	}
	else if (Cast<ACountess>(this))
	{
		pGM->UpdateAllPlayerHP(CurrentHP / MaxHP, TEXT("Countess"));
	}
}

void APlayerBase::SetWeaponCollision(bool bCollisionOn)
{
}

void APlayerBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APlayerBase, CurrentHP);
	DOREPLIFETIME(APlayerBase, CurPlayerState); 
	DOREPLIFETIME(APlayerBase, bIsAttackable);
}

float APlayerBase::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{	
	if (CurPlayerState == EPlayerState::Dead)
		return 0.0f;

	CurrentHP -= Damage;
	ABasicPC * pPC = Cast<ABasicPC>(GetController());
	if (!pPC)
		return 0.0f;

	ABasicGM * pGM = Cast<ABasicGM>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!pGM)
		return 0.0f;

	OnRep_CurrentHP();
	UpdateAllPlayerHPUI();

	if (CurrentHP <= 0)
	{
		S2A_Dead();
		S2A_PlayFadeOut();
		CurPlayerState = EPlayerState::Dead;

		pGM->RemoveAlivePlayer(Cast<APlayerController>(GetController()));
	}

	return 0.0f;
}

void APlayerBase::DoActorBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	//오버랩된 것이 몬스터인 경우 데미지 처리
	AMonsterBase * pMonster = Cast<AMonsterBase>(OtherActor);
	if (pMonster)
	{
		UGameplayStatics::ApplyDamage(pMonster, 20.0f, GetController(), this, NULL);
	}
}

void APlayerBase::C2S_NormalAttack_Implementation()
{
	S2A_NormalAttack();
}

void APlayerBase::S2A_NormalAttack_Implementation()
{
	FString Combo = "Combo";
	Combo.Append(FString::FromInt(CurrentCombo + 1));

	CurrentCombo = (CurrentCombo + 1) % MaxCombo;

	bIsAttackable = false;

	PlayAnimMontage(NormalAttackMontage, 1.0f, FName(*Combo));

	CurPlayerState = EPlayerState::Attack;
}

void APlayerBase::S2A_UpdateHPUI_Implementation(float HP, FName CharacterName)
{
	ABasicPC * pPC = Cast<ABasicPC>(GetController());
	if (pPC)
	{
		pPC->UpdateAllPlayerHP(HP, CharacterName);
	}
}

void APlayerBase::S2A_Dead_Implementation()
{
	PlayAnimMontage(DeadMontage,0.8f);
}

void APlayerBase::SetCurrentCombo(int iComboIdx)
{
	CurrentCombo = iComboIdx;
}
