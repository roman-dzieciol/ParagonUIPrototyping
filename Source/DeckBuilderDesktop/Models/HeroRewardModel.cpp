// Fill out your copyright notice in the Description page of Project Settings.

#include "DeckBuilderDesktop.h"
#include "HeroRewardModel.h"
#include "DataTables/FHeroSkinData.h"
#include "DataTables/FHeroEmoteData.h"
#include "DataTables/FHeroRewardData.h"

UHeroRewardModel::UHeroRewardModel(class FObjectInitializer const & ObjectInitializer)
	: Super(ObjectInitializer)
{

}

UHeroRewardModel* UHeroRewardModel::ConstructFromHeroRewardData(const FHeroRewardData& HeroRewardData, FString HeroName, UDataTable* RewardTable, UDataTable* HeroSkinTable, UDataTable* HeroEmoteTable)
{
	auto HeroRewardModel = NewObject<UHeroRewardModel>(GetTransientPackage(), NAME_None);
	HeroRewardModel->Title = HeroRewardData.Title;
	HeroRewardModel->MatchXPBoost = HeroRewardData.MatchXPBoost;
	HeroRewardModel->MatchTeamXPBoost = HeroRewardData.MatchTeamXPBoost;

	auto RewardModel = NewObject<URewardModel>(GetTransientPackage(), NAME_None);
	HeroRewardModel->Reward = RewardModel;

	if (HeroRewardData.Reward.Equals("ChallengerSkin"))
	{
		FString SkinRowName = FString::Printf(TEXT("%s_Challenger"), *HeroName);
		FHeroSkinData* SkinRow = HeroSkinTable->FindRow<FHeroSkinData>(FName(*SkinRowName, FNAME_Find), TEXT(" UHeroRewardModel::ConstructFromHeroRewardData"));
		check(SkinRow != nullptr);
		RewardModel->RewardName = SkinRow->Title;
		RewardModel->RewardType = TEXT("Skin");
		RewardModel->Description = SkinRow->Description;
		RewardModel->Icon = SkinRow->IconTexture;
	}
	else if (HeroRewardData.Reward.Equals("MasterSkin"))
	{
		FString SkinRowName = FString::Printf(TEXT("%s_Master"), *HeroName);
		FHeroSkinData* SkinRow = HeroSkinTable->FindRow<FHeroSkinData>(FName(*SkinRowName, FNAME_Find), TEXT(" UHeroRewardModel::ConstructFromHeroRewardData"));
		check(SkinRow != nullptr);
		RewardModel->RewardName = SkinRow->Title;
		RewardModel->RewardType = TEXT("Skin");
		RewardModel->Description = SkinRow->Description;
		RewardModel->Icon = SkinRow->IconTexture;
	}
	else if (HeroRewardData.Reward.Equals("Emote"))
	{
		FString EmoteRowName = FString::Printf(TEXT("%sEmote"), *HeroName);
		FHeroEmoteData* EmoteRow = HeroEmoteTable->FindRow<FHeroEmoteData>(FName(*EmoteRowName, FNAME_Find), TEXT(" UHeroRewardModel::ConstructFromHeroRewardData"));
		check(EmoteRow != nullptr);
		RewardModel->RewardName = EmoteRow->Title;
		RewardModel->RewardType = TEXT("Emote");
		RewardModel->Description = EmoteRow->Description;
		RewardModel->Icon = EmoteRow->Icon;
	}
	else 
	{
		FRewardData* RewardRow = RewardTable->FindRow<FRewardData>(FName(*HeroRewardData.Reward, FNAME_Find), TEXT(" UHeroRewardModel::ConstructFromHeroRewardData"));
		check(RewardRow != nullptr);
		RewardModel->RewardName = RewardRow->RewardName;
		RewardModel->RewardType = RewardRow->RewardType;
		RewardModel->Description = RewardRow->Description;
		RewardModel->Icon = RewardRow->Icon;
	}

	return HeroRewardModel;
}

