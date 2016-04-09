// Fill out your copyright notice in the Description page of Project Settings.

#include "DeckBuilderDesktop.h"
#include "CardFilterOr.h"

UCardFilterOr::UCardFilterOr(class FObjectInitializer const & ObjectInitializer)
	: Super(ObjectInitializer)
{
	static FName FNAME_CardFilterOr_Generic(TEXT("Or"));
	FilterName = FNAME_CardFilterOr_Generic;
}

bool UCardFilterOr::IsMatching(UCardModel* CardModel) const
{
	if (Filters.Num() > 0)
	{
		for (auto Filter : Filters)
		{
			if (Filter->IsMatching(CardModel))
			{
				return true;
			}
		}
		return false;
	}
	return true;
}


void UCardFilterOr::RemoveFiltersMatching(FName FilterName, FText DisplayName, FText DisplayValue)
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

void UCardFilterOr::RemoveFilter(UCardFilter* FilterToRemove)
{
	Filters.Remove(FilterToRemove);
	for (auto Filter : Filters)
	{
		Filter->RemoveFilter(FilterToRemove);
	}
}

