// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "QuestSettings.generated.h"

class UQuestCondition;
/**
 * 
 */
UCLASS()
class P00_TEST_API UQuestSettings : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	FText Name;
	
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<UQuestCondition>> StartConditions;
	
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<UQuestCondition>> StopConditions;
};
