// Fill out your copyright notice in the Description page of Project Settings.

#include "DeckBuilderDesktop.h"
#include "CardFilterMain.h"

#pragma region Internal

UCardFilterMain::UCardFilterMain(class FObjectInitializer const & ObjectInitializer)
	: Super(ObjectInitializer)
{
	ConstructSubFilters();
}

UCardFilterMain* UCardFilterMain::ConstructCardFilterMain(FName InFilterType, ECardFilterGroupMatching InMatching)
{
	auto Filter = NewObject<UCardFilterMain>(GetTransientPackage(), NAME_None);
	Filter->FilterName = InFilterType;
	Filter->Matching = InMatching;
	return Filter;
}

void UCardFilterMain::ConstructSubFilters()
{
	// Search by text filter, configured by user
	TextFilter = UCardFilterByStat::ConstructCardFilterByStat(FName(TEXT("Text")), TEXT("CardName"), FString(), false);
	AddFilter(TextFilter);

	// Deck affinity filters, configured by app
	AffinityFilterGroup = UCardFilterGroup::ConstructCardFilterGroup(FName(TEXT("AffinityGroup")), ECardFilterGroupMatching::Any);
	AddFilter(AffinityFilterGroup);

	// Card slot filters, configured by user
	SlotFilterGroup = UCardFilterGroup::ConstructCardFilterGroup(FName(TEXT("Slot")), ECardFilterGroupMatching::Any);
	SlotFilterGroup->LocalizedName = FText::FromString(TEXT("Slot"));
	AddFilter(SlotFilterGroup);

	// Base stat filters, configured by user
	BaseStatFilterGroup = UCardFilterGroup::ConstructCardFilterGroup(FName(TEXT("Stat")), ECardFilterGroupMatching::Any);
	BaseStatFilterGroup->LocalizedName = FText::FromString(TEXT("Stat"));
	AddFilter(BaseStatFilterGroup);

	// Base stat filters, configured by user
	CostValueFilterGroup = UCardFilterGroup::ConstructCardFilterGroup(FName(TEXT("Cost")), ECardFilterGroupMatching::Any);
	CostValueFilterGroup->LocalizedName = FText::FromString(TEXT("Cost"));
	AddFilter(CostValueFilterGroup);
}

#pragma endregion Internal


#pragma region SubFilters

void UCardFilterMain::FilterByText(const FString& Text)
{
	check(TextFilter != nullptr);
	check(TextFilter->IsValidLowLevel());
	UE_LOG(Deck, Verbose, TEXT("UCardFilterMain::FilterByText: %s"), *Text);
	TextFilter->StatContains = Text;
}

void UCardFilterMain::FilterByAffinities(TArray<FString> AffinityNames)
{
	check(AffinityFilterGroup != nullptr);
	check(AffinityFilterGroup->IsValidLowLevel());
	UE_LOG(Deck, Verbose, TEXT("UCardFilterMain::FilterByAffinities: %s"), *FString::Join(AffinityNames, TEXT(", ")));
	AffinityFilterGroup->RemoveAllFilters();
	for (auto AffinityName : AffinityNames)
	{
		AffinityFilterGroup->AddFilter(UCardFilterByStat::ConstructCardFilterByStat(FName(TEXT("Affinity")), TEXT("Affinity"), AffinityName, false));
	}
}

void UCardFilterMain::FilterBySlot(const FString& SlotName)
{
	check(SlotFilterGroup != nullptr);
	check(SlotFilterGroup->IsValidLowLevel());
	UE_LOG(Deck, Verbose, TEXT("UCardFilterMain::FilterBySlot: %s"), *SlotName);
	
	SlotFilterGroup->LocalizedValue = FText::FromString(SlotName);
	SlotFilterGroup->RemoveAllFilters();

	if (SlotName.Equals(TEXT("Equipment")))
	{
		SlotFilterGroup->AddFilter(UCardFilterByStat::ConstructCardFilterByStat(FName(TEXT("Slot")), TEXT("Type"), TEXT("Active"), true));
		SlotFilterGroup->AddFilter(UCardFilterByStat::ConstructCardFilterByStat(FName(TEXT("Slot")), TEXT("Type"), TEXT("Passive"), true));
	}
	else if (!SlotName.IsEmpty())
	{
		SlotFilterGroup->AddFilter(UCardFilterByStat::ConstructCardFilterByStat(FName(TEXT("Slot")), TEXT("Type"), SlotName, true));
	}
}

void UCardFilterMain::FilterByBaseStats(const TArray<FString> StatNames)
{
	check(BaseStatFilterGroup != nullptr);
	check(BaseStatFilterGroup->IsValidLowLevel());
	UE_LOG(Deck, Verbose, TEXT("UCardFilterMain::FilterByBaseStats: %s"), *FString::Join(StatNames, TEXT(", ")));

	BaseStatFilterGroup->RemoveAllFilters();
	for (auto StatName : StatNames)
	{
		auto StatFilter = UCardFilterByStat::ConstructCardFilterByStat(FName(TEXT("Stat")), StatName, FString(), false);
		StatFilter->LocalizedValue = FText::FromString(StatName);
		BaseStatFilterGroup->AddFilter(StatFilter);
	}
}

void UCardFilterMain::FilterByCostValues(const TArray<int32> CostValues)
{
	check(CostValueFilterGroup != nullptr);
	check(CostValueFilterGroup->IsValidLowLevel());
	UE_LOG(Deck, Verbose, TEXT("UCardFilterMain::FilterByCostValues: %s"), *FString::Join(CostValues, TEXT(", ")));

	CostValueFilterGroup->RemoveAllFilters();
	for (auto CostValue : CostValues)
	{
		CostValueFilterGroup->AddFilter(UCardFilterByStat::ConstructCardFilterByStat(FName(TEXT("Cost")), TEXT("Cost"), FString::FromInt(CostValue), true));
	}
}

TArray<UCardFilter*> UCardFilterMain::GetDisplayableFilters() const
{
	check(TextFilter != nullptr && TextFilter->IsValidLowLevel());
	check(SlotFilterGroup != nullptr && SlotFilterGroup->IsValidLowLevel());
	check(BaseStatFilterGroup != nullptr && BaseStatFilterGroup->IsValidLowLevel());
	check(CostValueFilterGroup != nullptr && CostValueFilterGroup->IsValidLowLevel());

	TArray<UCardFilter*> DisplayableFilters;

	if (!TextFilter->StatContains.IsEmpty())
	{
		DisplayableFilters.Add(TextFilter);
	}

	if (SlotFilterGroup->Filters.Num() > 0)
	{
		DisplayableFilters.Add(SlotFilterGroup);
	}

	DisplayableFilters.Append(BaseStatFilterGroup->Filters);
	DisplayableFilters.Append(CostValueFilterGroup->Filters);

	return DisplayableFilters;
}

void UCardFilterMain::ClearFilter(UCardFilter* Filter)
{
	check(Filter != nullptr && Filter->IsValidLowLevel());

	if (TextFilter == Filter)
	{
		FilterByText(FString());
	}
	else if (SlotFilterGroup == Filter)
	{
		FilterBySlot(FString());
	}
	else if (BaseStatFilterGroup == Filter)
	{
		FilterByBaseStats(TArray<FString>());
	}
	else if (CostValueFilterGroup == Filter)
	{
		FilterByCostValues(TArray<int32>());
	}
}

void UCardFilterMain::ClearAllFilters()
{
	ClearFilter(TextFilter);
	ClearFilter(SlotFilterGroup);
	ClearFilter(BaseStatFilterGroup);
	ClearFilter(CostValueFilterGroup);
}

#pragma endregion SubFilters
