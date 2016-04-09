// Fill out your copyright notice in the Description page of Project Settings.

#include "DeckBuilderDesktop.h"
#include "CardFilterAnd.h"



UCardFilterAnd::UCardFilterAnd(class FObjectInitializer const & ObjectInitializer)
	: Super(ObjectInitializer)
{
	static FName FNAME_CardFilterAnd_Generic(TEXT("And"));
	FilterName = FNAME_CardFilterAnd_Generic;
}

bool UCardFilterAnd::IsMatching(UCardModel* CardModel) const
{
	for (auto Filter : Filters)
	{
		if (!Filter->IsMatching(CardModel))
		{
			return false;
		}
	}
	return true;
}


void UCardFilterAnd::RemoveFiltersMatching(FName FilterName, FText DisplayName, FText DisplayValue)
{
	Filters.RemoveAll([=](UCardFilter* Filter) {
		if (!FilterName.IsEqual(NAME_None) && !Filter->FilterName.IsEqual(FilterName)) {
			return false;
		}
		if (!DisplayName.IsEmptyOrWhitespace() && !Filter->GetDisplayName().EqualToCaseIgnored(DisplayName)) {
			return false;
		}
		if (!DisplayValue.IsEmptyOrWhitespace() && !Filter->GetDisplayValue().EqualToCaseIgnored(DisplayValue)) {
			return false;
		}
		return true;
	});
	for (auto Filter : Filters)
	{
		Filter->RemoveFiltersMatching(FilterName, DisplayName, DisplayValue);
	}
}

void UCardFilterAnd::RemoveFilter(UCardFilter* FilterToRemove)
{
	Filters.Remove(FilterToRemove);
	for (auto Filter : Filters)
	{
		Filter->RemoveFilter(FilterToRemove);
	}
}
