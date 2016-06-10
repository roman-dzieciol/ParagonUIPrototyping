// Fill out your copyright notice in the Description page of Project Settings.

#include "DeckBuilderDesktop.h"
#include "HeroSkinModel.h"


UHeroSkinModel::UHeroSkinModel(class FObjectInitializer const & ObjectInitializer)
	: Super(ObjectInitializer)
{
}


UHeroSkinModel* UHeroSkinModel::ConstructFromHeroSkinData(const FHeroSkinData& HeroSkinData)
{
	auto HeroSkinModel = NewObject<UHeroSkinModel>(GetTransientPackage(), NAME_None);
	HeroSkinModel->SkinName = HeroSkinData.SkinName;
	HeroSkinModel->Title = HeroSkinData.Title;
	HeroSkinModel->Description = HeroSkinData.Description;
	HeroSkinModel->IconTexture = HeroSkinData.IconTexture;
	HeroSkinModel->PreviewTexture = HeroSkinData.PreviewTexture;
	HeroSkinModel->Cost = HeroSkinData.Cost;
	return HeroSkinModel;
}

