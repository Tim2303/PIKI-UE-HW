// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest.h"
#include "QuestSettings.h"

#include "QuestCondition.h"
#include "QuestSystemComponent.h"
#include "GameFramework/GameModeBase.h"

int32 bDebugInstantFinish = 0;
FAutoConsoleVariableRef CVarDebugInstantFinish(TEXT("quest.InstantFinish"),
	bDebugInstantFinish, TEXT("Debug Instantly Finish Quests"),
	ECVF_Cheat);

// Sets default values
AQuest::AQuest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AQuest::UpdateStartStatus()
{
	if (QuestStatus != EQuestStatus::WaitingForStart)
	{
		return;
	}
	
	for (UQuestCondition *Condition : StartConditions)
	{
		if (!ensure(Condition))
		{
			return;
		}
		if (!Condition->IsCompleted())
		{
			return;
		}
	}
	
	if (bDebugInstantFinish)
	{
		QuestStatus = EQuestStatus::Completed;
		return;
	}
	
	for (const UQuestCondition* ConditionTemplate : QuestSettings->EndConditionsInst)
	{
		if (!ensureMsgf(ConditionTemplate, TEXT("Bad setup for quest %s"), *GetNameSafe(this)))
		{
			return;
		}
		
		UQuestCondition *QuestCondition = DuplicateObject<UQuestCondition>(ConditionTemplate, this);
		QuestCondition->bIsEndCondition = true;
		
		QuestCondition->StartCondition();
		QuestCondition->OnQuestConditionCompleted.AddUObject(this, &AQuest::UpdateEndStatus);
		
		EndConditions.Add(QuestCondition);
	}
	
	SetQuestStatus(EQuestStatus::Started);
}

void AQuest::UpdateEndStatus()
{
	for (UQuestCondition *Condition : EndConditions)
	{
		if (!ensure(Condition))
		{
			return;
		}
		if (!Condition->IsCompleted())
		{
			return;
		}
	}
	
	SetQuestStatus(EQuestStatus::Completed);
}

void AQuest::SetQuestStatus(EQuestStatus NewStatus)
{
	if (QuestStatus == NewStatus)
	{
		return;
	}
	
	QuestStatus = NewStatus;
	OnQuestStatusChanged.Broadcast(this, QuestStatus);
}

// Called when the game starts or when spawned
void AQuest::BeginPlay()
{
	Super::BeginPlay();
	
	UQuestSystemComponent *QuestSystemComponent =
		GetWorld()->GetAuthGameMode()->GetComponentByClass<UQuestSystemComponent>();
	if (QuestSystemComponent)
	{
		QuestSystemComponent->RegisterQuest(this);
	}
	
	for (const UQuestCondition* ConditionTemplate : QuestSettings->StartConditionsInst)
	{
		if (!ensureMsgf(ConditionTemplate, TEXT("Bad setup for quest %s"), *GetNameSafe(this)))
		{
			return;
		}
		
		UQuestCondition *QuestCondition = DuplicateObject<UQuestCondition>(ConditionTemplate, this);
		QuestCondition->OnQuestConditionCompleted.AddUObject(this, &AQuest::UpdateStartStatus);
		StartConditions.Add(QuestCondition);
		
		QuestCondition->StartCondition();
	}
}

// Called every frame
void AQuest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
