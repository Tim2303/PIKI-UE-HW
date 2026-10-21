// Fill out your copyright notice in the Description page of Project Settings.


#include "NextFrameSuccess_QuestCondition.h"

void UNextFrameSuccess_QuestCondition::StartCondition()
{
	UE_LOG(LogQuest, Log, TEXT("NextFrameSuccess condition %s: start, will succeed next tick"), *GetNameSafe(this));
	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &UNextFrameSuccess_QuestCondition::Success);
}

void UNextFrameSuccess_QuestCondition::StopCondition()
{
	// Super::StopCondition();
	UE_LOG(LogQuest, Log, TEXT("NextFrameSuccess condition %s: stop"), *GetNameSafe(this));
}

void UNextFrameSuccess_QuestCondition::Success()
{
	Complete();
	UE_LOG(LogQuest, Verbose, TEXT("NextFrameSuccess condition %s: Success tick"), *GetNameSafe(this));
}
