// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestCondition.h"

void UQuestCondition::Complete()
{
	bCompleted = true;
	OnQuestConditionCompleted.Broadcast();
}
