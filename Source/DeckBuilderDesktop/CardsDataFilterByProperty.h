// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CardsDataFilter.h"
#include "CardsDataFilterByProperty.generated.h"

/**
 * 
 */
UCLASS()
class DECKBUILDERDESKTOP_API UCardsDataFilterByProperty : public UCardsDataFilter
{
	GENERATED_UCLASS_BODY()

public:
	virtual TArray<FCardData> FilteredCardsData(TArray<FCardData> CardsData) override;
	
};
