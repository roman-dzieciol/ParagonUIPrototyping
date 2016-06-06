// Fill out your copyright notice in the Description page of Project Settings.

#include "DeckBuilderDesktop.h"
#include "HeroAbilityModel.h"


UHeroAbilityModel::UHeroAbilityModel(class FObjectInitializer const & ObjectInitializer)
	: Super(ObjectInitializer)
{
}


UHeroAbilityModel* UHeroAbilityModel::ConstructFromHeroAbilityData(const FHeroAbilityData& HeroAbilityData)
{
	auto HeroAbilityModel = NewObject<UHeroAbilityModel>(GetTransientPackage(), NAME_None);
	HeroAbilityModel->AbilityName = HeroAbilityData.AbilityName;
	HeroAbilityModel->Title = HeroAbilityData.Title;
	HeroAbilityModel->Description = HeroAbilityData.Description;
	HeroAbilityModel->ManaCost = HeroAbilityData.ManaCost;
	HeroAbilityModel->Cooldown = HeroAbilityData.Cooldown;
	HeroAbilityModel->IconTexture = HeroAbilityData.IconTexture;
	return HeroAbilityModel;
}

