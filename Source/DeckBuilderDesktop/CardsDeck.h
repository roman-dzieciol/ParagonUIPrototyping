// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "FCardData.h"
#include "CardsDeck.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class DECKBUILDERDESKTOP_API UCardsDeck : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Deck)
	TArray<FCardData> Cards;
	
	UFUNCTION(BlueprintCallable, Category = Deck)
	void AddCard(FCardData CardData);

	UFUNCTION(BlueprintCallable, Category = Deck)
	void RemoveCard(FCardData CardData);

	UFUNCTION(BlueprintCallable, Category = Deck)
	void RemoveAllCards();

	UFUNCTION(BlueprintCallable, Category = Deck)
	void RemoveAllCardsOfType(FString CardType);

	UFUNCTION(BlueprintCallable, Category = Deck)
	TArray<FCardData> GetAllCardsOfType(FString CardType);

	UFUNCTION(BlueprintCallable, Category = Deck)
	int32 CountOfCardsNamed(FString CardName);
};
