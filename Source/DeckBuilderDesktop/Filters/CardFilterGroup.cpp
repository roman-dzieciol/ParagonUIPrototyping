// Fill out your copyright notice in the Description page of Project Settings.

#include "DeckBuilderDesktop.h"
#include "CardFilterGroup.h"




UCardFilterGroup::UCardFilterGroup(class FObjectInitializer const & ObjectInitializer)
	: Super(ObjectInitializer)
{
	static FName FNAME_CardFilterGroup_Generic(TEXT("Group"));
	FilterName = FNAME_CardFilterGroup_Generic;
}

UCardFilterGroup* UCardFilterGroup::ConstructCardFilterGroup(FName InFilterType, ECardFilterGroupMatching InMatching)
{
	UCardFilterGroup* Filter = NewObject<UCardFilterGroup>(GetTransientPackage(), NAME_None);
	Filter->FilterName = InFilterType;
	Filter->Matching = InMatching;
	return Filter;
}

bool UCardFilterGroup::IsMatching(UCardModel* CardModel) const
{
	switch (Matching) {
	case ECardFilterGroupMatching::All: {
		for (auto Filter : Filters)
		{
			if (!Filter->IsMatching(CardModel))
			{
				return false;
			}
		}
		break;
	}
	case ECardFilterGroupMatching::Any: {
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
		break;
	}
	}
	return true;
}


void UCardFilterGroup::RemoveFiltersMatching(FName FilterName, FText DisplayName, FText DisplayValue)
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

void UCardFilterGroup::RemoveFilter(UCardFilter* FilterToRemove)
{
	Filters.Remove(FilterToRemove);
	for (auto Filter : Filters)
	{
		Filter->RemoveFilter(FilterToRemove);
	}
}

void UCardFilterGroup::AddFilter(UCardFilter* FilterToAdd)
{
	check(FilterToAdd != nullptr);
	check(FilterToAdd->IsValidLowLevel());
	check(FilterToAdd->Parent == nullptr);

	if (FilterToAdd != nullptr && FilterToAdd->IsValidLowLevel())
	{
		Filters.Add(FilterToAdd);
		FilterToAdd->Parent = this;
	}
}

void UCardFilterGroup::RemoveAllFilters()
{
	for (auto Filter : Filters)
	{
		Filter->Parent = nullptr;
	}
	Filters.Empty();
}

TArray<UCardFilter*> UCardFilterGroup::FindFiltersMatching(FName FilterName, FText DisplayName, FText DisplayValue) const
{
	TArray<UCardFilter*> Result;
	for (auto Filter : Filters)
	{
		Result.Append(Filter->FindFiltersMatching(FilterName, DisplayName, DisplayValue));
	}
	return Result;
}