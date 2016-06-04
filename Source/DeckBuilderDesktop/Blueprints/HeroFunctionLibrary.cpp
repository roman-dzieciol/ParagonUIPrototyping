// Fill out your copyright notice in the Description page of Project Settings.

#include "DeckBuilderDesktop.h"
#include "HeroFunctionLibrary.h"
#include "Models/HeroListModel.h"

UHeroListModel* UHeroFunctionLibrary::ConstructHeroListFromHeroDataTable(UDataTable* HeroDataTable, UDataTable* HeroAbilityTable)
{
	return UHeroListModel::ConstructFromHeroDataTable(HeroDataTable, HeroAbilityTable);
}


UTexture2D* UHeroFunctionLibrary::LoadKeyTextureNamed(const FString& KeyName)
{
	FString TexturePath = FString::Printf(TEXT("/Game/Art/Keys/T_Keys_%s.T_Keys_%s"), *KeyName, *KeyName);
	return LoadObject<UTexture2D>(NULL, *TexturePath, NULL, LOAD_NoWarn | LOAD_Quiet, NULL);
}

