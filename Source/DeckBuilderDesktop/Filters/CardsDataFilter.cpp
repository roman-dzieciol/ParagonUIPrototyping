// Fill out your copyright notice in the Description page of Project Settings.

#include "DeckBuilderDesktop.h"
#include "CardsDataFilter.h"



UCardsDataFilter::UCardsDataFilter(class FObjectInitializer const & ObjectInitializer)
	: Super(ObjectInitializer)
{
	static FName FNAME_CardsDataFilter_Generic(TEXT("Generic"));
	TypeName = FNAME_CardsDataFilter_Generic;
}

TArray<FCardData> UCardsDataFilter::FilteredCardsData(TArray<FCardData> CardsData)
{
	return CardsData;
}

bool UCardsDataFilter::IsActive()
{
	return ValueString.Len() > 0;
}

