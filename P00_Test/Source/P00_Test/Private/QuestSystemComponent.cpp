// Fill out your copyright notice in the Description page of Project Settings.

#include "QuestSystemComponent.h"

#include "EngineUtils.h"
#include "Quest.h"
#include "QuestCondition.h"

// Sets default values for this component's properties
UQuestSystemComponent::UQuestSystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UQuestSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	// for (TActorIterator<AQuest> It(GetWorld(), AQuest::StaticClass()); It; ++It)
	// {
	// 	ActiveQuests.AddUnique(*It);
	// }
	
	for (const TSubclassOf<AQuest>& QuestClass : Quests)
	{
		if (!QuestClass)
		{
			UE_LOG(LogQuest, Warning, TEXT("QuestSystem: empty quest class in Quests array"));
			continue;
		}
		
		AQuest *Quest = GetWorld()->SpawnActor<AQuest>(QuestClass);
		ActiveQuests.AddUnique(Quest);
	}
}


// Called every frame
void UQuestSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UQuestSystemComponent::RegisterQuest(AQuest* NewQuest)
{
	const int32 Index = ActiveQuests.AddUnique(NewQuest);
	UE_LOG(LogQuest, Log, TEXT("QuestSystem: registered quest %s (index %d, total %d)"),
		*GetNameSafe(NewQuest), Index, ActiveQuests.Num());
}

void UQuestSystemComponent::GetActiveAndStartedQuests(TArray<AQuest*>& OutQuests)
{
	for (AQuest* Quest : ActiveQuests)
	{
		if (Quest->GetQuestStatus() == EQuestStatus::Started)
		{
			OutQuests.Add(Quest);
		}
	}
}

void UQuestSystemComponent::GetCompletedQuests(TArray<AQuest*>& OutQuests)
{
	for (AQuest* Quest : ActiveQuests)
	{
		if (Quest->GetQuestStatus() == EQuestStatus::Completed)
		{
			OutQuests.Add(Quest);
		}
	}
}
