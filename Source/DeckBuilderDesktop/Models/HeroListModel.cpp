// Fill out your copyright notice in the Description page of Project Settings.

#include "DeckBuilderDesktop.h"
#include "HeroListModel.h"
#include "HeroModel.h"


UHeroListModel::UHeroListModel(class FObjectInitializer const & ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UHeroListModel* UHeroListModel::ConstructFromHeroDataTable(UDataTable* HeroDataTable, UDataTable* HeroAbilityTable, UDataTable* HeroSkinTable)
{
	check(HeroDataTable != nullptr);

	auto HeroListModel = NewObject<UHeroListModel>(GetTransientPackage(), NAME_None);
	for (auto RowName : HeroDataTable->GetRowNames())
	{
		FHeroData* Row = HeroDataTable->FindRow<FHeroData>(RowName, TEXT(" UHeroListModel::LoadCardsFromDataTable"));
		if (Row != nullptr)
		{
			UHeroModel* HeroModel = UHeroModel::ConstructFromHeroData(*Row, HeroAbilityTable, HeroSkinTable);
			if (HeroModel != nullptr)
			{
				HeroListModel->HeroModels.Add(HeroModel);
				HeroListModel->HeroModelsByName.Add(HeroModel->HeroName, HeroModel);
			}
		}
	}
	return HeroListModel;
}

UHeroModel* UHeroListModel::GetHeroModelNamed(FString HeroName) const
{
	UHeroModel*const* FoundModel = HeroModelsByName.Find(HeroName);
	return FoundModel != nullptr ? *FoundModel : nullptr;
}

