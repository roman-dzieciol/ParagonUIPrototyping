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
	GENERATED_UCLASS_BODY()
	
public:
	// Reference to type of card
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Deck Item")
	UCardModel* CardModel;

	// Linked cards
	UPROPERTY()
	TArray<UDeckItemModel*> LinkedDeckItems;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Deck Item")
	UDeckItemModel* LinkingDeckItem;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Deck Item")
	int32 LinkedCardsLimit;

public:

	UFUNCTION(BlueprintCallable, Category = "Deck Item")
	TArray<UDeckItemModel*> GetLinkedDeckItems() const
	{
		return LinkedDeckItems;
	}

	UFUNCTION(BlueprintCallable, Category = "Deck Item")
	bool LinkWithItem(UDeckItemModel* DeckItem);

	UFUNCTION(BlueprintCallable, Category = "Deck Item")
	void UnlinkWithItem(UDeckItemModel* DeckItem);

	UFUNCTION(BlueprintCallable, Category = "Deck Item")
	void UnlinkAllItems();

	UFUNCTION(BlueprintCallable, Category = "Deck Item")
	int32 GetItemCount() const;

	UFUNCTION(BlueprintCallable, Category = "Deck Item")
	bool CanLinkItem(UDeckItemModel* DeckItem) const;

	UFUNCTION(BlueprintCallable, Category = "Deck Item")
	void OnRemove();

public:
	// Named constructor
	UFUNCTION(BlueprintCallable, Category = "Deck Item")
	static UDeckItemModel* ConstructDeckItemModel(UCardModel* ForCardModel);
};
