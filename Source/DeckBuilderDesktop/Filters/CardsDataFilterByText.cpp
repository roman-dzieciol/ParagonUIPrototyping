// Fill out your copyright notice in the Description page of Project Settings.

#include "DeckBuilderDesktop.h"
#include "CardsDataFilterByText.h"


UCardsDataFilterByText::UCardsDataFilterByText(class FObjectInitializer const & ObjectInitializer)
	: Super(ObjectInitializer)
{
	static FName FNAME_CardsDataFilter_ByText(TEXT("Text"));
	TypeName = FNAME_CardsDataFilter_ByText;
}

TArray<FCardData> UCardsDataFilterByText::FilteredCardsData(TArray<FCardData> CardsData)
{
	if (IsActive())
	{
		return CardsData.FilterByPredicate([=](const FCardData& CardData)
		{
			return CardData.CardName.Contains(ValueString);
		});
	}
	return CardsData;
}

