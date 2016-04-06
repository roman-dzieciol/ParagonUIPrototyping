// Fill out your copyright notice in the Description page of Project Settings.

#include "DeckBuilderDesktop.h"
#include "CardsDataFilterByAnyFilter.h"



UCardsDataFilterByAnyFilter::UCardsDataFilterByAnyFilter(class FObjectInitializer const & ObjectInitializer)
	: Super(ObjectInitializer)
{
	static FName FNAME_CardsDataFilter_ByAnyFilter(TEXT("AnyFilter"));
	TypeName = FNAME_CardsDataFilter_ByAnyFilter;
}

TArray<FCardData> UCardsDataFilterByAnyFilter::FilteredCardsData(TArray<FCardData> CardsData)
{
	if (IsActive())
	{
		TArray<FCardData> Result;
		for (auto Filter: Filters)
		{
			TArray<FCardData> FilterOutput = Filter->FilteredCardsData(CardsData);
			for (auto& CardData : FilterOutput)
			{
				Result.AddUnique(CardData);
			}
		}
		return Result;
	}
	return CardsData;
}

bool UCardsDataFilterByAnyFilter::IsActive()
{
	return Filters.Num() > 0;
}

