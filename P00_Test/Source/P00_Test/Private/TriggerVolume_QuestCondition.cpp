// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerVolume_QuestCondition.h"

#include "Quest.h"

void UTriggerVolume_QuestCondition::StartCondition()
{
	AQuest* Quest = Cast<AQuest>(GetOuter());
	if (!ensure(Quest))
	{
		UE_LOG(LogQuest, Error, TEXT("TriggerVolume condition %s: outer is not AQuest (%s)"),
			*GetNameSafe(this), *GetNameSafe(GetOuter()));
		return;
	}
	
	UE_LOG(LogQuest, Log, TEXT("TriggerVolume condition %s: start, waiting for %s overlap with tag '%s'"),
		*GetNameSafe(this), bIsEndCondition ? TEXT("end") : TEXT("begin"), *OtherTag.ToString());
	
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
		UE_LOG(LogQuest, Error, TEXT("TriggerVolume condition %s: stop failed, outer is not AQuest"), *GetNameSafe(this));
		return;
	}
	
	UE_LOG(LogQuest, Log, TEXT("TriggerVolume condition %s: stop"), *GetNameSafe(this));

	Quest->OnActorBeginOverlap.RemoveDynamic(this, &UTriggerVolume_QuestCondition::OnOverlapEvent);
	Quest->OnActorEndOverlap.RemoveDynamic(this, &UTriggerVolume_QuestCondition::OnOverlapEvent);
}

void UTriggerVolume_QuestCondition::OnOverlapEvent(AActor* OverlappedActor, AActor* OtherActor)
{
	if (!OtherActor)
	{
		UE_LOG(LogQuest, Warning, TEXT("TriggerVolume condition %s: overlap with null actor"), *GetNameSafe(this));
		return;
	}

	const bool bHasTag = OtherActor->ActorHasTag(OtherTag);
	UE_LOG(LogQuest, Log, TEXT("TriggerVolume condition %s: overlap with %s, %s '%s'"),
		*GetNameSafe(this), *OtherActor->GetName(),
		bHasTag ? TEXT("has tag") : TEXT("no tag"), *OtherTag.ToString());
	
	if (OtherActor && OtherActor->ActorHasTag(OtherTag))
	{
		Complete();
		StopCondition();
	}
}
