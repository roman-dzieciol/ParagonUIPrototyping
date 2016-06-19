// Fill out your copyright notice in the Description page of Project Settings.

#include "DeckBuilderDesktop.h"
#include "RewardFunctionLibrary.h"
#include "DataTables/FRewardData.h"
#include "Models/DailyRewardModel.h"
#include "Models/DailyRewardListModel.h"
#include "Models/HeroRewardModel.h"


UDailyRewardListModel* URewardFunctionLibrary::ConstructSampleDailyRewardListFromDataTable(FString CurrentReward, int32 CurrentDay, bool bEarned, TArray<FString> UpcomingRewards, UDataTable* RewardDataTable)
{
	UDailyRewardListModel* RewardListModel = NewObject<UDailyRewardListModel>(GetTransientPackage(), NAME_None);
	RewardListModel->bEarnedDailyReward = bEarned;

	FRewardData* CurrentRow = RewardDataTable->FindRow<FRewardData>(FName(*CurrentReward, FNAME_Find), TEXT(" URewardFunctionLibrary::ConstructSampleDailyRewardListFromDataTable"));
	UDailyRewardModel* CurrentRewardModel = UDailyRewardModel::ConstructFromRewardData(*CurrentRow);
	CurrentRewardModel->Day = CurrentDay;
	RewardListModel->CurrentDailyReward = CurrentRewardModel;

	auto TimeOffset = FTimespan(20, 42, 0);
	RewardListModel->UpcomingRewardAvailableAt = FDateTime::Now() + TimeOffset;

	for (auto RewardName : UpcomingRewards)
	{
		FRewardData* Row = RewardDataTable->FindRow<FRewardData>(FName(*RewardName, FNAME_Find), TEXT(" URewardFunctionLibrary::ConstructSampleDailyRewardListFromDataTable"));
		UDailyRewardModel* RewardModel = UDailyRewardModel::ConstructFromRewardData(*Row);
		RewardModel->Day = ++CurrentDay;
		RewardListModel->UpcomingDailyRewards.Add(RewardModel);
	}

	return RewardListModel;
}

UHeroRewardModel* URewardFunctionLibrary::ConstructHeroReward(const FHeroRewardData& HeroRewardData, FString HeroName, UDataTable* RewardTable, UDataTable* HeroSkinTable, UDataTable* HeroEmoteTable)
{
	return UHeroRewardModel::ConstructFromHeroRewardData(HeroRewardData, HeroName, RewardTable, HeroSkinTable, HeroEmoteTable);
}

