// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "DailyRewardModel.h"
#include "DailyRewardListModel.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class DECKBUILDERDESKTOP_API UDailyRewardListModel : public UObject
{
	GENERATED_UCLASS_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Daily Reward List")
		TArray<UDailyRewardModel*> UpcomingDailyRewards;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Daily Reward List")
		UDailyRewardModel* CurrentDailyReward;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Daily Reward List")
		bool bEarnedDailyReward;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Daily Reward List")
		FDateTime UpcomingRewardAvailableAt;
	
};
