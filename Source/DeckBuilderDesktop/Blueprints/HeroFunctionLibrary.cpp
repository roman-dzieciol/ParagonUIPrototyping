// Fill out your copyright notice in the Description page of Project Settings.

#include "DeckBuilderDesktop.h"
#include "HeroFunctionLibrary.h"
#include "Models/HeroListModel.h"

UHeroListModel* UHeroFunctionLibrary::ConstructHeroListFromHeroDataTable(UDataTable* HeroDataTable)
{
	return UHeroListModel::ConstructFromHeroDataTable(HeroDataTable);
}


