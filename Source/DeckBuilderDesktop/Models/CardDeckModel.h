// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Models/CardModel.h"
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
	TMap<UCardModel*,uint32> Cards;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Deck")
	int32 MaxCardCount;
	
	UFUNCTION(BlueprintCallable, Category = "Deck")
	void AddCard(UCardModel* CardModel);

	UFUNCTION(BlueprintCallable, Category = "Deck")
	void RemoveCard(UCardModel* CardModel);

	UFUNCTION(BlueprintCallable, Category = "Deck")
	void RemoveAllCards();

	UFUNCTION(BlueprintCallable, Category = "Deck")
	void RemoveAllCardsOfType(FString CardType);

	UFUNCTION(BlueprintCallable, Category = "Deck")
	TArray<UCardModel*> GetAllCardsOfType(FString CardType);

	UFUNCTION(BlueprintCallable, Category = "Deck")
	int32 CountOfCard(UCardModel* CardModel);

	UFUNCTION(BlueprintCallable, Category = "Deck")
	int32 CountOfAllCards();
};
