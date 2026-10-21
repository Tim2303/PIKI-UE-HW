// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuestCondition.h"
#include "NextFrameSuccess_QuestCondition.generated.h"

/**
 * 
 */
UCLASS()
class P00_TEST_API UNextFrameSuccess_QuestCondition : public UQuestCondition
{
	GENERATED_BODY()
public:
	virtual void StartCondition() override;
	virtual void StopCondition() override;
	
	UFUNCTION()
	void Success();
};
