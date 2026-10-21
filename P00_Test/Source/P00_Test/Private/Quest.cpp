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
		UE_LOG(LogQuest, Verbose, TEXT("Quest %s: UpdateStartStatus ignored, status is %s"),
			*GetNameSafe(this), *UEnum::GetValueAsString(QuestStatus));
		return;
	}
	
	for (UQuestCondition *Condition : StartConditions)
	{
		if (!ensure(Condition))
		{
			UE_LOG(LogQuest, Error, TEXT("Quest %s: null start condition"), *GetNameSafe(this));
			return;
		}
		if (!Condition->IsCompleted())
		{
			UE_LOG(LogQuest, Verbose, TEXT("Quest %s: start condition %s not completed yet"),
				*GetNameSafe(this), *GetNameSafe(Condition));
			return;
		}
	}
	
	if (bDebugInstantFinish)
	{
		SetQuestStatus(EQuestStatus::Completed);
		return;
	}
	
	for (const UQuestCondition* ConditionTemplate : QuestSettings->EndConditionsInst)
	{
		if (!ensureMsgf(ConditionTemplate, TEXT("Bad setup for quest %s"), *GetNameSafe(this)))
		{
			UE_LOG(LogQuest, Error, TEXT("Quest %s: null end condition template in %s"),
				*GetNameSafe(this), *GetNameSafe(QuestSettings));
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
			UE_LOG(LogQuest, Error, TEXT("Quest %s: null end condition"), *GetNameSafe(this));
			return;
		}
		if (!Condition->IsCompleted())
		{
			UE_LOG(LogQuest, Verbose, TEXT("Quest %s: end condition %s not completed yet"),
				*GetNameSafe(this), *GetNameSafe(Condition));
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
	
	UE_LOG(LogQuest, Log, TEXT("Quest %s: status %s -> %s"), *GetNameSafe(this),
		*UEnum::GetValueAsString(QuestStatus), *UEnum::GetValueAsString(NewStatus));
	
	QuestStatus = NewStatus;
	OnQuestStatusChanged.Broadcast(this, QuestStatus);
}

// Called when the game starts or when spawned
void AQuest::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogQuest, Log, TEXT("Quest %s: BeginPlay"), *GetNameSafe(this));

	if (!ensureMsgf(QuestSettings, TEXT("Quest %s has no QuestSettings"), *GetNameSafe(this)))
	{
		UE_LOG(LogQuest, Error, TEXT("Quest %s: QuestSettings is not set, quest will not work"), *GetNameSafe(this));
		return;
	}
	
	UQuestSystemComponent *QuestSystemComponent =
		GetWorld()->GetAuthGameMode()->GetComponentByClass<UQuestSystemComponent>();
	if (QuestSystemComponent)
	{
		QuestSystemComponent->RegisterQuest(this);
	} else
	{
		UE_LOG(LogQuest, Warning, TEXT("Quest %s: QuestSystemComponent not found on GameMode, quest not registered"),
			*GetNameSafe(this));
	}
	
	for (const UQuestCondition* ConditionTemplate : QuestSettings->StartConditionsInst)
	{
		if (!ensureMsgf(ConditionTemplate, TEXT("Bad setup for quest %s"), *GetNameSafe(this)))
		{
			UE_LOG(LogQuest, Error, TEXT("Quest %s: null start condition template in %s"),
				*GetNameSafe(this), *GetNameSafe(QuestSettings));
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
