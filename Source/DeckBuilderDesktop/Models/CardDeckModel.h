// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Models/CardModel.h"
#include "DeckItemModel.h"
#include "CardDeckModel.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class DECKBUILDERDESKTOP_API UCardDeckModel : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	UPROPERTY()
	TArray<UDeckItemModel*> DeckItems;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Deck")
	int32 MaxCardCount;

public:
	UFUNCTION(BlueprintCallable, Category = "Deck")
	void AddCard(UCardModel* UCardModel);

	UFUNCTION(BlueprintCallable, Category = "Deck")
	void AddDeckItem(UDeckItemModel* DeckItem);

	UFUNCTION(BlueprintCallable, Category = "Deck")
	void RemoveDeckItem(UDeckItemModel* DeckItem);

	UFUNCTION(BlueprintCallable, Category = "Deck")
	void RemoveAllCards();

	UFUNCTION(BlueprintCallable, Category = "Deck")
	void RemoveAllCardsOfType(FString CardType);

	UFUNCTION(BlueprintCallable, Category = "Deck")
	TArray<UDeckItemModel*> GetAllCardsOfType(FString CardType) const;

	UFUNCTION(BlueprintCallable, Category = "Deck")
	int32 CountOfCard(UCardModel* UCardModel) const;

	UFUNCTION(BlueprintCallable, Category = "Deck")
	int32 CountOfAllCards() const;

	UFUNCTION(BlueprintCallable, Category = "Deck")
	bool CanAddCard() const;
};
