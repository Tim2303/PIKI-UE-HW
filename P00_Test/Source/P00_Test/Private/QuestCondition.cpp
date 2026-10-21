// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestCondition.h"

DEFINE_LOG_CATEGORY(LogQuest)
void UQuestCondition::Complete()
{
	bCompleted = true;
	OnQuestConditionCompleted.Broadcast();
}
