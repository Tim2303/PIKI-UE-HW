// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest.h"
#include "QuestSettings.h"

#include "QuestCondition.h"
#include "QuestSystemComponent.h"
// #include "Apple/ApplePlatform.h"
#include "GameFramework/GameModeBase.h"

// Sets default values
AQuest::AQuest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AQuest::UpdateStartStatus()
{
	for (UQuestCondition *Condition : StartConditions)
	{
		// if (!ensure(Condition))
		// {
		// 	return;
		// }
		if (!Condition->IsCompleted())
		{
			return;
		}
	}
	
	QuestStatus = EQuestStatus::Started;
	
	for (const TSubclassOf<UQuestCondition>& ConditionTemplate : QuestSettings->StopConditions)
	{
		// if (!ensureMsgf(ConditionTemplate, TEXT("Bad setup for quest %s"), *GetNameSafe(this)))
		// {
		// 	return;
		// }
		
		UQuestCondition *QuestCondition = NewObject<UQuestCondition>(this, ConditionTemplate);
		QuestCondition->StartCondition();
		QuestCondition->OnQuestConditionCompleted.AddUObject(this, &AQuest::UpdateEndStatus);
		
		EndConditions.Add(QuestCondition);
	}
}

void AQuest::UpdateEndStatus()
{
	for (UQuestCondition *Condition : EndConditions)
	{
		// if (!ensure(Condition))
		// {
		// 	return;
		// }
		if (!Condition->IsCompleted())
		{
			return;
		}
	}
	
	QuestStatus = EQuestStatus::Completed;
}

EQuestStatus AQuest::GetQuestStatus()
{
	return QuestStatus;
}

// Called when the game starts or when spawned
void AQuest::BeginPlay()
{
	Super::BeginPlay();
	
	UQuestSystemComponent *QuestSystemComponent = GetWorld()->GetAuthGameMode()->GetComponentByClass<UQuestSystemComponent>();
	if (QuestSystemComponent)
	{
		QuestSystemComponent->RegisterQuest(this);
	}
	
	for (const TSubclassOf<UQuestCondition>& ConditionTemplate : QuestSettings->StartConditions)
	{
		// if (!ensureMsgf(ConditionTemplate, TEXT("Bad setup for quest %s"), *GetNameSafe(this)))
		// {
		// 	return;
		// }
		
		UQuestCondition *QuestCondition = NewObject<UQuestCondition>(this, ConditionTemplate);
		QuestCondition->StartCondition();
		QuestCondition->OnQuestConditionCompleted.AddUObject(this, &AQuest::UpdateStartStatus);
		
		StartConditions.Add(QuestCondition);
	}
}

// Called every frame
void AQuest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
