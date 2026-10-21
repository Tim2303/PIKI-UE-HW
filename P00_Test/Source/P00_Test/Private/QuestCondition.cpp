// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestCondition.h"

DEFINE_LOG_CATEGORY(LogQuest)
void UQuestCondition::Complete()
{
	UE_LOG(LogQuest, Log, TEXT("Condition %s (outer: %s) completed. IsEndCondition=%s"),
		*GetNameSafe(this), *GetNameSafe(GetOuter()), bIsEndCondition ? TEXT("true") : TEXT("false"));
	
	bCompleted = true;
	OnQuestConditionCompleted.Broadcast();
}
