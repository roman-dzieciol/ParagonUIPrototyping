// Fill out your copyright notice in the Description page of Project Settings.

#include "DeckBuilderDesktop.h"
#include "CardFilterMain.h"
#include "Blueprints/CardsFunctionLibrary.h"

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
	SlotFilterGroup = UCardFilterGroup::ConstructCardFilterGroup(FName(TEXT("Card Type")), ECardFilterGroupMatching::Any);
	SlotFilterGroup->LocalizedName = FText::FromString(TEXT("Card Type"));
	AddFilter(SlotFilterGroup);

	// Base stat filters, configured by user
	BaseStatFilterGroup = UCardFilterGroup::ConstructCardFilterGroup(FName(TEXT("Stat")), ECardFilterGroupMatching::All);
	BaseStatFilterGroup->LocalizedName = FText::FromString(TEXT("Stat"));
	AddFilter(BaseStatFilterGroup);

	// Base stat filters, configured by user
	BaseStatInclusiveFilterGroup = UCardFilterGroup::ConstructCardFilterGroup(FName(TEXT("Stat")), ECardFilterGroupMatching::Any);
	BaseStatFilterGroup->AddFilter(BaseStatInclusiveFilterGroup);

	// Base stat filters, configured by user
	BaseStatExclusiveFilterGroup = UCardFilterGroup::ConstructCardFilterGroup(FName(TEXT("Stat")), ECardFilterGroupMatching::All);
	BaseStatFilterGroup->AddFilter(BaseStatExclusiveFilterGroup);

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

void UCardFilterMain::FilterBySlotNames(TArray<FString> SlotNames)
{
	check(SlotFilterGroup != nullptr);
	check(SlotFilterGroup->IsValidLowLevel());
	UE_LOG(Deck, Verbose, TEXT("UCardFilterMain::FilterBySlotNames: %s"), *FString::Join(SlotNames, TEXT(", ")));
	
	SlotFilterGroup->LocalizedValue = FText::FromString(FString::Join(SlotNames, TEXT(", ")));
	SlotFilterGroup->RemoveAllFilters();

	for (auto SlotName : SlotNames)
	{
		SlotFilterGroup->AddFilter(UCardFilterByStat::ConstructCardFilterByStat(FName(TEXT("Card Type")), TEXT("Type"), SlotName, true));
	}
}

void UCardFilterMain::FilterByBaseStats(const TArray<FString> StatNames)
{
	check(BaseStatFilterGroup != nullptr);
	check(BaseStatFilterGroup->IsValidLowLevel());
	UE_LOG(Deck, Verbose, TEXT("UCardFilterMain::FilterByBaseStats: %s"), *FString::Join(StatNames, TEXT(", ")));

	ClearBaseStatFilters();
	for (auto StatName : StatNames)
	{
		auto StatFilter = UCardFilterByStat::ConstructCardFilterByStat(FName(TEXT("Stats")), StatName, FString(), false);
		StatFilter->LocalizedValue = FText::FromString(StatName);
		BaseStatInclusiveFilterGroup->AddFilter(StatFilter);
	}
}

void UCardFilterMain::FilterByBaseStatModels(const TArray<UCardStatModel*>& StatModels)
{
	check(BaseStatFilterGroup != nullptr);
	check(BaseStatFilterGroup->IsValidLowLevel());
	UE_LOG(Deck, Verbose, TEXT("UCardFilterMain::FilterByBaseStatModels"));

	ClearBaseStatFilters();
	for (auto StatModel : StatModels)
	{
		FString StatNameString = UCardsFunctionLibrary::MakeValidTableRowName(StatModel->Type.ToString()).ToString();
		UE_LOG(Deck, Verbose, TEXT("UCardFilterMain::FilterByBaseStatModels# %s"), *StatModel->Type.ToString());
		auto StatFilter = UCardFilterByStat::ConstructCardFilterByStat(FName(TEXT("Stats")), StatNameString, FString(), false);
		StatFilter->LocalizedValue = StatModel->Type;
		StatFilter->Icon = StatModel->Icon;
		BaseStatInclusiveFilterGroup->AddFilter(StatFilter);
	}
}

void UCardFilterMain::ClearBaseStatFilters()
{
	check(BaseStatFilterGroup != nullptr);
	check(BaseStatFilterGroup->IsValidLowLevel());
	UE_LOG(Deck, Verbose, TEXT("UCardFilterMain::ClearBaseStatFilters"));
	BaseStatInclusiveFilterGroup->RemoveAllFilters();
	BaseStatExclusiveFilterGroup->RemoveAllFilters();
}

void UCardFilterMain::AddBaseStatFilters(const TArray<UCardFilterByStat*>& StatFilters)
{
	check(BaseStatFilterGroup != nullptr);
	check(BaseStatFilterGroup->IsValidLowLevel());
	UE_LOG(Deck, Verbose, TEXT("UCardFilterMain::AddBaseStatFilters"));
	for (auto StatFilter : StatFilters)
	{
		if (StatFilter->bDisabled)
		{
			continue;
		}
		else if (StatFilter->bExclusive)
		{
			BaseStatExclusiveFilterGroup->AddFilter(StatFilter);
		}
		else 
		{
			BaseStatInclusiveFilterGroup->AddFilter(StatFilter);
		}
	}
}

void UCardFilterMain::FilterByCostValues(const TArray<int32> CostValues)
{
	check(CostValueFilterGroup != nullptr);
	check(CostValueFilterGroup->IsValidLowLevel());

	//FString::Join does not support TArray<int32>?
	//UE_LOG(Deck, Verbose, TEXT("UCardFilterMain::FilterByCostValues: %s"), *FString::Join(CostValues, TEXT(", ")));

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

	if (BaseStatFilterGroup->Filters.Num() > 0)
	{
		DisplayableFilters.Add(BaseStatFilterGroup);
	}

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
		FilterBySlotNames(TArray<FString>());
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
