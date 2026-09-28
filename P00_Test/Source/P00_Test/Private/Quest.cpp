// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest.h"
#include "QuestSettings.h"

#include "QuestCondition.h"
#include "QuestSystemComponent.h"
#include "GameFramework/GameModeBase.h"

// Sets default values
AQuest::AQuest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
		UQuestCondition *QuestCondition = NewObject<UQuestCondition>(this, ConditionTemplate);
		QuestCondition->StartCondition();
		StartConditions.Add(QuestCondition);
	}
}

// Called every frame
void AQuest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

