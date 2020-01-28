// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerBox_Stage.h"
#include "Monster/MonsterBase.h"

void ATriggerBox_Stage::BeginPlay()
{
	Super::BeginPlay();
}


ATriggerBox_Stage::ATriggerBox_Stage()
{
}

void ATriggerBox_Stage::RemoveMonster(AMonsterBase * pTargetMonster)
{
	if (!pTargetMonster)
		return;
		
	StageMonster.Remove(pTargetMonster);
	if (StageMonster.Num() == 0)
		StageClear();
}

void ATriggerBox_Stage::StageStart()
{
}

void ATriggerBox_Stage::StageClear()
{
}