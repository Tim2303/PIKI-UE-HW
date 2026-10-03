// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuestCondition.h"
#include "TriggerVolume_QuestCondition.generated.h"

/**
 * 
 */
UCLASS()
class P00_TEST_API UTriggerVolume_QuestCondition : public UQuestCondition
{
	GENERATED_BODY()
	
public:
	virtual void StartCondition() override;
	virtual void StopCondition() override;
	
	UFUNCTION()
	void OnOverlapEvent(AActor* OverlappedActor, AActor* OtherActor);
	
	UPROPERTY(EditAnywhere)
	FName OtherTag;
	
	// true: on exit, false on entering
	UPROPERTY(EditAnywhere)
	bool bCompleteOnExit = false;
};
