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
	
	if (bIsEndCondition)
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
	UE_LOG(LogQuest, Log, TEXT("Quest Condition Overlaped with actor %s with has tag %s"), *OtherActor->GetName(),
		OtherActor->ActorHasTag(OtherTag)? TEXT("has tag") : TEXT("no tag"));
	AQuest* Quest =Cast<AQuest>(GetOuter());
	FVector Center;
	FVector Extents;
	Quest->GetActorBounds(true, Center, Extents, false);
	UE_VLOG_BOX(Quest, LogQuest, Error, FBox(Center - Extents, Center + Extents), FColor::Orange, TEXT(""));
	
	if (OtherActor && OtherActor->ActorHasTag(OtherTag))
	{
		Complete();
		StopCondition();
	}
}
