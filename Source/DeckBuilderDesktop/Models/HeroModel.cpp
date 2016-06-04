// Fill out your copyright notice in the Description page of Project Settings.

#include "DeckBuilderDesktop.h"
#include "HeroModel.h"
#include "HeroAbilityModel.h"

UHeroModel::UHeroModel(class FObjectInitializer const & ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UHeroModel* UHeroModel::ConstructFromHeroData(const FHeroData& HeroData, UDataTable* HeroAbilityTable)
{
	check(HeroAbilityTable != nullptr);

	auto HeroModel = NewObject<UHeroModel>(GetTransientPackage(), NAME_None);
	HeroModel->HeroName = HeroData.HeroName;
	HeroModel->AvatarTexture = HeroData.AvatarTexture;
	HeroModel->HeroSelectTexture = HeroData.HeroSelectTexture;
	HeroModel->Affinities = HeroData.Affinities;
	HeroModel->RecommendedStats = HeroData.RecommendedStats;
	HeroModel->NotRecommendedStats = HeroData.NotRecommendedStats;

	for (auto AbilityName : HeroData.Abilities)
	{
		FHeroAbilityData* AbilityRow = HeroAbilityTable->FindRow<FHeroAbilityData>(FName(*AbilityName, FNAME_Find), TEXT(" UHeroModel::ConstructFromHeroData"));
		check(AbilityRow != nullptr);
		
		UHeroAbilityModel* AbilityModel = UHeroAbilityModel::ConstructFromHeroAbilityData(*AbilityRow);
		check(AbilityModel != nullptr);
		HeroModel->Abilities.Add(AbilityModel);
	}

	return HeroModel;
}
