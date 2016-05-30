// Fill out your copyright notice in the Description page of Project Settings.

#include "DeckBuilderDesktop.h"
#include "DailyRewardModel.h"

UDailyRewardModel::UDailyRewardModel(class FObjectInitializer const & ObjectInitializer)
	: Super(ObjectInitializer)
{

}

UDailyRewardModel* UDailyRewardModel::ConstructFromRewardData(const FRewardData& RewardData)
{
	auto RewardModel = NewObject<UDailyRewardModel>(GetTransientPackage(), NAME_None);
	RewardModel->RewardName = RewardData.RewardName;
	RewardModel->RewardType = RewardData.RewardType;
	RewardModel->Description = RewardData.Description;
	RewardModel->Icon = RewardData.Icon;
	return RewardModel;
}

