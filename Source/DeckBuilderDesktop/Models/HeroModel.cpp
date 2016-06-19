// Fill out your copyright notice in the Description page of Project Settings.

#include "DeckBuilderDesktop.h"
#include "HeroModel.h"
#include "HeroAbilityModel.h"
#include "HeroSkinModel.h"

UHeroModel::UHeroModel(class FObjectInitializer const & ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UHeroModel* UHeroModel::ConstructFromHeroData(const FHeroData& HeroData, UDataTable* HeroAbilityTable, UDataTable* HeroSkinTable)
{
	check(HeroAbilityTable != nullptr);

	auto HeroModel = NewObject<UHeroModel>(GetTransientPackage(), NAME_None);
	HeroModel->HeroID = HeroData.HeroID;
	HeroModel->HeroName = HeroData.HeroName;
	HeroModel->TutorialTexture = HeroData.TutorialTexture;
	HeroModel->AvatarTexture = HeroData.AvatarTexture;
	HeroModel->Affinities = HeroData.Affinities;
	HeroModel->RecommendedStats = HeroData.RecommendedStats;
	HeroModel->NotRecommendedStats = HeroData.NotRecommendedStats;
	HeroModel->Difficulty = HeroData.Difficulty;
	HeroModel->BasicAttack = HeroData.BasicAttack;
	HeroModel->AbilityPower = HeroData.AbilityPower;
	HeroModel->Durability = HeroData.Durability;
	HeroModel->Mobility = HeroData.Mobility;

	for (auto AbilityName : HeroData.Abilities)
	{
		FHeroAbilityData* AbilityRow = HeroAbilityTable->FindRow<FHeroAbilityData>(FName(*AbilityName, FNAME_Find), TEXT(" UHeroModel::ConstructFromHeroData"));
		check(AbilityRow != nullptr);
		
		UHeroAbilityModel* AbilityModel = UHeroAbilityModel::ConstructFromHeroAbilityData(*AbilityRow);
		check(AbilityModel != nullptr);
		HeroModel->Abilities.Add(AbilityModel);
	}

	for (auto SkinName : HeroData.Skins)
	{
		auto SkinRowName = FString::Printf(TEXT("%s_%s"), *HeroModel->HeroID , *SkinName);
		FHeroSkinData* SkinRow = HeroSkinTable->FindRow<FHeroSkinData>(FName(*SkinRowName, FNAME_Find), TEXT(" UHeroModel::ConstructFromHeroData"));
		check(SkinRow != nullptr);

		UHeroSkinModel* SkinModel = UHeroSkinModel::ConstructFromHeroSkinData(*SkinRow);
		check(SkinModel != nullptr);
		HeroModel->Skins.Add(SkinModel);
	}

	if (HeroModel->Skins.Num() > 0)
	{
		HeroModel->SelectedSkin = HeroModel->Skins[0];
	}

	HeroModel->HeroLevel = FMath::RandRange(1, 10);

	return HeroModel;
}

void UHeroModel::SelectSkin(UHeroSkinModel* HeroSkinModel)
{
	SelectedSkin = HeroSkinModel;
	OnHeroModelUpdated.Broadcast();
}