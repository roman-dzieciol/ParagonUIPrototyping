// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "DataTables/FRewardData.h"
#include "DailyRewardModel.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class DECKBUILDERDESKTOP_API UDailyRewardModel : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Daily Reward")
		FString RewardName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Daily Reward")
		FString RewardType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Daily Reward")
		FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Daily Reward")
		int32 Day;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Daily Reward")
		UTexture2D* Icon;

public:
	static UDailyRewardModel* ConstructFromRewardData(const FRewardData& RewardData);
	
	
};
