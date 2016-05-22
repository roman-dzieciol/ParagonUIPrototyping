// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "DeckListModel.generated.h"

class UCardDeckModel;
class UCardListModel;
class UHeroListModel;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class DECKBUILDERDESKTOP_API UDeckListModel : public UObject
{
	GENERATED_UCLASS_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Deck List")
	TArray<UCardDeckModel*> DeckSlots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Deck List")
	int32 DeckSlotsCount;
	
public:
	UFUNCTION(BlueprintCallable, Category = "Deck List")
	UCardDeckModel* CreateNewDeck();

	UFUNCTION(BlueprintCallable, Category = "Deck List")
	bool RemoveDeckModel(UCardDeckModel* CardDeckModel);

	UFUNCTION(BlueprintCallable, Category = "Deck List")
	bool SaveDecks();

	UFUNCTION(BlueprintCallable, Category = "Deck List")
	bool LoadDecks(UCardListModel* CardListModel, UHeroListModel* HeroListModel);
};
