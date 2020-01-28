// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"

AMonsterAIController::AMonsterAIController()
{
	BTComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BTComponent"));
	BBComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BBComponent"));

}


void AMonsterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AMonsterBase * Monster = Cast<AMonsterBase>(InPawn);
	if (Monster && Monster->MonsterBT && BTComponent && BBComponent)
	{
		//블랙보드 초기화
		BBComponent->InitializeBlackboard(*(Monster->MonsterBT->BlackboardAsset));

		//트리 초기화
		BTComponent->StartTree(*(Monster->MonsterBT));
	}
}

void AMonsterAIController::OnUnPossess()
{
	Super::OnUnPossess();
}

void AMonsterAIController::SetTarget(FVector NewTarget)
{
	BBComponent->SetValueAsVector(TEXT("Target"), NewTarget);
}

void AMonsterAIController::SetState(EMonsterState NewState)
{
	BBComponent->SetValueAsEnum(TEXT("MonsterCurrentState"), (uint8)NewState);
}

void AMonsterAIController::SetPlayer(AActor * Target)
{
	if (Target)
	{
		BBComponent->SetValueAsObject(TEXT("Player"), Target);
	}
}

void AMonsterAIController::SetReStart(bool bIsReStart)
{
	BBComponent->SetValueAsBool(TEXT("bIsReStart"), bIsReStart);
}

void AMonsterAIController::StopBT()
{
	BTComponent->StopLogic(FString());
}

void AMonsterAIController::ReStartBT()
{
	BBComponent->SetValueAsBool(TEXT("bIsReStart"), true);

	BTComponent->RestartLogic();
}
