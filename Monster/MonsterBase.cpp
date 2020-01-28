// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Monster/MonsterAIController.h"
#include "Player/PlayerBase.h"
#include "Widget/MonsterHPBarWidgetBase.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Level/Stage/TriggerBox_Stage.h"
#include "UnrealNetwork.h"

// Sets default values
AMonsterBase::AMonsterBase()
{
 	// Set this character to \ Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//PawnSesning �ʱ� ����
	//---------------------------------------
	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));
	//---------------------------------------

	//Mesh �ʱ� ����
	//---------------------------------------
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -120.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetRelativeScale3D(FVector(1.2f));
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	//---------------------------------------

	//Capsule �ʱ� ���� 
	//---------------------------------------
	GetCapsuleComponent()->SetCapsuleHalfHeight(120.0f);
	GetCapsuleComponent()->SetCapsuleRadius(50.0f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Monster"));
	//---------------------------------------

	//HPBar �ʱ� ����
	//---------------------------------------
	HPBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBar"));
	HPBar->SetupAttachment(GetMesh());
	//---------------------------------------

}

// Called when the game starts or when spawned
void AMonsterBase::BeginPlay()
{
	Super::BeginPlay();
	CurrentHP = MaxHP;


	if (PawnSensing)
	{
		PawnSensing->OnSeePawn.AddDynamic(this, &AMonsterBase::SeenPawn);
		PawnSensing->SetActive(false);
	}
}

// Called every frame
void AMonsterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (MonsterState != EMonsterState::Normal && MonsterState != EMonsterState::Dead)
	{
		LookPlayer(DeltaTime);
	}
}

// Called to bind functionality to input
void AMonsterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMonsterBase::SetState(EMonsterState NewState)
{
	AMonsterAIController * AIController = Cast<AMonsterAIController>(GetController());
	if (Controller)
	{
		MonsterState = NewState;
		AIController->SetState(NewState);
	}
}

void AMonsterBase::LookPlayer(float DeltaTime)
{
	//���͸� �������� �÷��̾ ���������� �������� �Ǵ�

	//������ ������ ���� ���͸� �����´�.
	FVector MonsterRightVector = GetActorRightVector();

	if (!TargetPlayer)
		return;
	//���Ϳ��� �÷��̾�� ���� ���͸� �����´�.
	FVector MonsterToPlayerVector = TargetPlayer->GetActorLocation() - GetActorLocation();
	MonsterToPlayerVector = UKismetMathLibrary::Normal(MonsterToPlayerVector);


	//���� �̹� �÷��̾� ������ ���������� �ȿ����δ�.
	float fDotValue = UKismetMathLibrary::Dot_VectorVector(MonsterToPlayerVector, GetActorForwardVector());

	if (fDotValue > 0.9f)
		return;


	//���� ����
	fDotValue = UKismetMathLibrary::Dot_VectorVector(MonsterRightVector, MonsterToPlayerVector);

	FRotator MonsterRotation = GetActorRotation();

	if (fDotValue < 0)
	{
		SetActorRotation(FRotator(MonsterRotation.Pitch
			, MonsterRotation.Yaw - 270 * DeltaTime,
			MonsterRotation.Roll));
	}
	else
	{
		SetActorRotation(FRotator(MonsterRotation.Pitch
			, MonsterRotation.Yaw + 270 * DeltaTime,
			MonsterRotation.Roll));
	}
}

void AMonsterBase::OnRep_CurrentHP()
{
	UpdateHPUI();
}

void AMonsterBase::UpdateHPUI()
{

}

void AMonsterBase::SeenPawn(APawn * Pawn)
{
	if (MonsterState == EMonsterState::Normal)
	{
		//���� ���� TargetOn���� ����
		MonsterState = EMonsterState::TargetOn;

		//Controller�� ���ؼ� BlackBoard���� �ٲ��ֱ�
		AMonsterAIController * AIController = Cast<AMonsterAIController>(GetController());
		if (AIController)
		{
			AIController->SetState(MonsterState);
			AIController->SetPlayer(Pawn);

			//Monster�� Attack �� �� �ʿ���
			TargetPlayer = Cast<APlayerBase>(Pawn);
		}
	}
}

void AMonsterBase::S2A_SpawnHitParticle_Implementation()
{
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(GetActorLocation() + FVector(0.0f, 0.0f, GetCapsuleComponent()->GetScaledCapsuleRadius() / 2));
	SpawnTransform.SetScale3D(FVector(2.0f, 2.0f, 2.0f));
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),
		HitParticle,
		SpawnTransform);
}

float AMonsterBase::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	if (!GetWorld()->IsServer())
	{
		return 0.0f;
	}
	//����ִ� ��쿡�� ������ ó��
	if (MonsterState != EMonsterState::Dead)
	{
		//HP ���̱�
		CurrentHP -= Damage;

		S2A_SpawnHitParticle();

		OnRep_CurrentHP();

		//ü��Ȯ��
		if (CurrentHP <= 0)
		{
			//Capsule Collision ����
			GetCapsuleComponent()->SetCollisionProfileName(TEXT("NoCollision"));

			//Stage���� �׾����� �˸���.
			if (pCurrentStage)
				pCurrentStage->RemoveMonster(this);

			DeadProc();
		}
	}

	return 0.0f;
}

void AMonsterBase::S2A_PlayPatternMontage_Implementation(FName PatternName)
{
	if (!bIsPlayingPattern)
	{
		PlayAnimMontage(PatternMontage, 1.0f, PatternName);
	}
}

void AMonsterBase::StopPatternMontage()
{
	StopAnimMontage(PatternMontage);
}

void AMonsterBase::DeadProc()
{
	//���� ���� ���� ���� ����
	MonsterState = EMonsterState::Dead;

	AMonsterAIController * AIController = Cast<AMonsterAIController>(GetController());
	if (AIController)
	{
		AIController->ReStartBT();
		AIController->SetState(MonsterState);
	}
}

void AMonsterBase::SetPlayingPattern(bool bNewPatternState)
{
	bIsPlayingPattern = bNewPatternState;
}

bool AMonsterBase::IsPlayingPattern()
{
	return bIsPlayingPattern;
}

void AMonsterBase::DoActorBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	APlayerBase * pPlayer = Cast<APlayerBase>(OtherActor);
	if (pPlayer)
	{
		UGameplayStatics::ApplyDamage(pPlayer, 5.0f, GetController(), this, NULL);
	}
}

void AMonsterBase::SetWeaponCollision(bool bCollisionOn)
{
}

void AMonsterBase::AddStage(ATriggerBox_Stage * pStage)
{
	pCurrentStage = pStage;
}

void AMonsterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMonsterBase, MonsterState);
	DOREPLIFETIME(AMonsterBase, CurrentHP);
	DOREPLIFETIME(AMonsterBase, TargetPlayer);
}
