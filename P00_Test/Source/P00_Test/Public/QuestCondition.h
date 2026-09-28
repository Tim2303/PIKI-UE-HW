// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "QuestCondition.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class P00_TEST_API UQuestCondition : public UObject
{
	GENERATED_BODY()
	
public:
	virtual void StartCondition() PURE_VIRTUAL(UQuestCondition::StartCondition,);
	virtual void StopCondition() PURE_VIRTUAL(UQuestCondition::StopCondition,);
	
protected:
	UPROPERTY(BlueprintReadOnly)
	bool bCompleted = false;
	
};
