// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuestSystemComponent.generated.h"

class AQuest;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class P00_TEST_API UQuestSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UQuestSystemComponent();
	
	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void RegisterQuest(AQuest *NewQuest);
	
	UFUNCTION(BlueprintCallable)
	void GetActiveAndStartedQuests(TArray<AQuest*>& OutQuests);
	
	UFUNCTION(BlueprintCallable)
	void GetCompletedQuests(TArray<AQuest*>& OutQuests);
	
protected:
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AQuest>> Quests;
	
	UPROPERTY()
	TArray<AQuest*> ActiveQuests;
};
