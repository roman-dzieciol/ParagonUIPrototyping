// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CardsDataFilter.h"
#include "CardsDataFilterByAnyFilter.generated.h"

/**
 * 
 */
UCLASS()
class DECKBUILDERDESKTOP_API UCardsDataFilterByAnyFilter : public UCardsDataFilter
{
	GENERATED_UCLASS_BODY()


public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cards Data Filter")
	TArray<UCardsDataFilter*> Filters;

	virtual TArray<FCardData> FilteredCardsData(TArray<FCardData> CardsData) override;
	virtual bool IsActive() override;
};
