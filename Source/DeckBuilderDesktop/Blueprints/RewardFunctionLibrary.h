// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "RewardFunctionLibrary.generated.h"

class UDailyRewardListModel;
class UDataTable;

/**
 * 
 */
UCLASS()
class DECKBUILDERDESKTOP_API URewardFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	

public:
	UFUNCTION(BlueprintCallable, Category = "Reward Function Library")
		static UDailyRewardListModel* ConstructSampleDailyRewardListFromDataTable(FString CurrentReward, int32 CurrentDay, bool bEarned, TArray<FString> UpcomingRewards, UDataTable* RewardDataTable);

};
