// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerVolume_QuestCondition.h"

#include "Quest.h"

void UTriggerVolume_QuestCondition::StartCondition()
{
	AQuest* Quest = Cast<AQuest>(GetOuter());
	if (!ensure(Quest))
	{
		return;
	}
	
	if (bCompleteOnExit)
	{
		Quest->OnActorEndOverlap.AddDynamic(this, &UTriggerVolume_QuestCondition::OnOverlapEvent);
	} else
	{
		Quest->OnActorBeginOverlap.AddDynamic(this, &UTriggerVolume_QuestCondition::OnOverlapEvent);
	}
}

void UTriggerVolume_QuestCondition::StopCondition()
{
	AQuest* Quest = Cast<AQuest>(GetOuter());
	if (!ensure(Quest))
	{
		return;
	}
	
	Quest->OnActorBeginOverlap.RemoveDynamic(this, &UTriggerVolume_QuestCondition::OnOverlapEvent);
	Quest->OnActorEndOverlap.RemoveDynamic(this, &UTriggerVolume_QuestCondition::OnOverlapEvent);
}

void UTriggerVolume_QuestCondition::OnOverlapEvent(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor && OtherActor->ActorHasTag(OtherTag))
	{
		Complete();
		StopCondition();
	}
}
