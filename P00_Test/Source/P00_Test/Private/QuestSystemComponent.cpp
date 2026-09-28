// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestSystemComponent.h"

#include "AndroidRuntimeSettings.h"
#include "EngineUtils.h"
#include "Quest.h"

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

	for (TActorIterator<AQuest> It(GetWorld(), AQuest::StaticClass()); It; ++It)
	{
		ActiveQuests.AddUnique(*It);
	}
	
	for (const TSubclassOf<AQuest>& QuestClass : Quests)
	{
		AQuest *Quest = GetWorld()->SpawnActor<AQuest>(QuestClass);
		ActiveQuests.Add(Quest);
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
	ActiveQuests.AddUnique(NewQuest);
}

