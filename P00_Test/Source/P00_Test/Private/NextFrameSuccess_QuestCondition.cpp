// Fill out your copyright notice in the Description page of Project Settings.


#include "NextFrameSuccess_QuestCondition.h"

void UNextFrameSuccess_QuestCondition::StartCondition()
{
	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &UNextFrameSuccess_QuestCondition::Success);
}

void UNextFrameSuccess_QuestCondition::StopCondition()
{
	// Super::StopCondition();
}

void UNextFrameSuccess_QuestCondition::Success()
{
	Complete();
}
