// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "CardModel.h"
#include "DeckItemModel.generated.h"

/**
 * Card deck item
 */
UCLASS(Blueprintable, BlueprintType)
class DECKBUILDERDESKTOP_API UDeckItemModel : public UObject
{
	GENERATED_BODY()
	
public:
	// Reference to type of card
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Deck Item")
	UCardModel* CardModel;

	// Linked cards
	// Consider these a part of the deck
	UPROPERTY()
	TArray<UDeckItemModel*> LinkedDeckItems;

public:

	UFUNCTION(BlueprintCallable, Category = "Deck Item")
	TArray<UDeckItemModel*> GetLinkedDeckItems() const
	{
		return LinkedDeckItems;
	}

	UFUNCTION(BlueprintCallable, Category = "Deck Item")
	void LinkWithCard(UCardModel* CardModelToLink);

	UFUNCTION(BlueprintCallable, Category = "Deck Item")
	void UnlinkWithDeckItem(UDeckItemModel* DeckItem);

	UFUNCTION(BlueprintCallable, Category = "Deck Item")
	void UnlinkAllCards();

public:
	// Named constructor
	UFUNCTION(BlueprintCallable, Category = "Deck Item")
	static UDeckItemModel* ConstructDeckItemModel(UCardModel* ForCardModel);
};
