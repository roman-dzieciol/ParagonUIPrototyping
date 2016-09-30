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
	if (bDisabled)
	{
		return true;
	}

	auto EffectiveFilters = Filters.FilterByPredicate([](UCardFilter* Filter) {
		return !Filter->bDisabled;
	});

	switch (Matching) {
	case ECardFilterGroupMatching::All: {
		for (auto Filter : EffectiveFilters)
		{
			if (!Filter->IsMatching(CardModel))
			{
				return false;
			}
		}
		return true;
	}
	case ECardFilterGroupMatching::Any: {
		if (EffectiveFilters.Num() > 0)
		{
			for (auto EffectiveFilter : EffectiveFilters)
			{
				if (EffectiveFilter->IsMatching(CardModel))
				{
					return true;
				}
			}
			return false;
		}
		return true;
	}
	}
	return true;
}


void UCardFilterGroup::RemoveFiltersMatching(FName Name, FText DisplayName, FText DisplayValue)
{
	Filters.RemoveAll([=](UCardFilter* Filter) {
		if (!FilterName.IsEqual(NAME_None) && !Filter->FilterName.IsEqual(Name)) {
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
		Filter->RemoveFiltersMatching(Name, DisplayName, DisplayValue);
	}
}

void UCardFilterGroup::RemoveFilter(UCardFilter* FilterToRemove)
{
	UE_LOG(Deck, Verbose, TEXT("UCardFilter::RemoveFilter: %s from: %s"), *FilterToRemove->ToString(), *ToString());
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

	Filters.Add(FilterToAdd);
	FilterToAdd->Parent = this;
}

void UCardFilterGroup::RemoveAllFilters()
{
	for (auto Filter : Filters)
	{
		Filter->Parent = nullptr;
	}
	Filters.Empty();
}

TArray<UCardFilter*> UCardFilterGroup::FindFiltersMatching(FName Name, FText DisplayName, FText DisplayValue) const
{
	TArray<UCardFilter*> Result;
	for (auto Filter : Filters)
	{
		Result.Append(Filter->FindFiltersMatching(Name, DisplayName, DisplayValue));
	}
	return Result;
}