// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "CardDeckImporterJSON.generated.h"

class UCardDeckModel;
class UCardListModel;
class UHeroListModel;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class DECKBUILDERDESKTOP_API UCardDeckImporterJSON : public UObject
{
	GENERATED_UCLASS_BODY()
	
public:
	UCardDeckModel* ImportDeckModel(const FString& InJSONData, UCardListModel* CardListModel, UHeroListModel* HeroListModel, TArray<FString>& OutErrors);
};
