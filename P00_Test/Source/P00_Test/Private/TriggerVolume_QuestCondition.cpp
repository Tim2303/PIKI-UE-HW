// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerVolume_QuestCondition.h"

#include "Quest.h"

void UTriggerVolume_QuestCondition::StartCondition()
{
	AQuest* Quest = Cast<AQuest>(GetOuter());
	Quest->OnActorBeginOverlap.AddDynamic(this, &UTriggerVolume_QuestCondition::StartOverlap);
}

void UTriggerVolume_QuestCondition::StopCondition()
{
	Super::StopCondition();
}

void UTriggerVolume_QuestCondition::StartOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor->ActorHasTag(OtherTag))
	{
		// TODO
	}
}
