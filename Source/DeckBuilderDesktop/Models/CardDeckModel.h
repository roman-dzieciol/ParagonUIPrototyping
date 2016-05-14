// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Models/CardModel.h"
#include "DeckItemModel.h"
#include "CardDeckModel.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCardDeckUpdated);

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

	UPROPERTY(EditAnywhere, BlueprintAssignable, Category = "Deck")
	FCardDeckUpdated OnCardDeckUpdated;

public:
	UFUNCTION(BlueprintCallable, Category = "Deck")
	bool AddCard(UCardModel* UCardModel);

	UFUNCTION(BlueprintCallable, Category = "Deck")
	bool AddDeckItem(UDeckItemModel* DeckItem);

	UFUNCTION(BlueprintCallable, Category = "Deck")
	bool AddDeckItemAndLinkWith(UDeckItemModel* DeckItem, UDeckItemModel* LinkingItem);

	UFUNCTION(BlueprintCallable, Category = "Deck")
	bool CanAddDeckItem(UDeckItemModel* DeckItem) const;

	UFUNCTION(BlueprintCallable, Category = "Deck")
	void RemoveDeckItem(UDeckItemModel* DeckItem);

	UFUNCTION(BlueprintCallable, Category = "Deck")
	void RemoveAllCards();

	UFUNCTION(BlueprintCallable, Category = "Deck")
	void RemoveAllCardsOfType(FString CardType);

	UFUNCTION(BlueprintCallable, Category = "Deck")
	TArray<UDeckItemModel*> GetAllCardsOfType(FString CardType) const;

	UFUNCTION(BlueprintCallable, Category = "Deck")
	int32 GetCountOfCard(UCardModel* UCardModel) const;

	UFUNCTION(BlueprintCallable, Category = "Deck")
	int32 GetCountOfAllCards() const;

	UFUNCTION(BlueprintCallable, Category = "Deck")
	bool CanAddCard() const;


private:

	bool InternalAddDeckItem(UDeckItemModel* DeckItem);
	void InternalRemoveDeckItem(UDeckItemModel* DeckItem);

private:
	TMultiMap<UCardModel*, UDeckItemModel*> DeckItemsByCardModel;

	void IncrementInUseCount(UDeckItemModel* DeckItem);
	void DecrementInUseCount(UDeckItemModel* DeckItem);


};
