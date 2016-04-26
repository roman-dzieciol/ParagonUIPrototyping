// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Filters/CardFilterGroup.h"
#include "Filters/CardFilterByStat.h"
#include "CardFilterMain.generated.h"

/**
 * The main card filter
 * Controls all the specific subfilters
 */
UCLASS(Blueprintable, BlueprintType)
class DECKBUILDERDESKTOP_API UCardFilterMain : public UCardFilterGroup
{
	GENERATED_UCLASS_BODY()

public:

	// Named constructor
	UFUNCTION(BlueprintCallable, Category = "Card Filter Main")
	static UCardFilterMain* ConstructCardFilterMain(FName InFilterType, ECardFilterGroupMatching InMatching);

public: 

	// The search text filter
	UPROPERTY()
	UCardFilterByStat* TextFilter;

	UFUNCTION(BlueprintCallable, Category = "Card Filter")
	void FilterByText(const FString& Text);

	UFUNCTION(BlueprintCallable, Category = "Card Filter")
	UCardFilterByStat* GetTextFilter() const 
	{
		return TextFilter;
	}

public:

	// The affinity filter
	UPROPERTY()
	UCardFilterGroup* AffinityFilterGroup;

	UFUNCTION(BlueprintCallable, Category = "Card Filter")
	void FilterByAffinities(TArray<FString> AffinityNames);

public:

	// The card slot filters
	UPROPERTY()
	UCardFilterGroup* SlotFilterGroup;

	UFUNCTION(BlueprintCallable, Category = "Card Filter")
	void FilterBySlot(const FString& SlotName);

	UFUNCTION(BlueprintCallable, Category = "Card Filter")
	UCardFilter* GetSlotFilter() const
	{
		return SlotFilterGroup;
	}

public:

	// The base stat filters
	UPROPERTY()
	UCardFilterGroup* BaseStatFilterGroup;

	UFUNCTION(BlueprintCallable, Category = "Card Filter")
	void FilterByBaseStats(const TArray<FString> StatNames);

	UFUNCTION(BlueprintCallable, Category = "Card Filter")
	TArray<UCardFilter*> GetBaseStatFilters() const
	{
		return BaseStatFilterGroup->Filters;
	}


public:

	// The card cost filters
	UPROPERTY()
	UCardFilterGroup* CostValueFilterGroup;

	UFUNCTION(BlueprintCallable, Category = "Card Filter")
	void FilterByCostValues(const TArray<int32> CostValues);

	UFUNCTION(BlueprintCallable, Category = "Card Filter")
	TArray<UCardFilter*> GetCostValueFilters() const
	{
		return CostValueFilterGroup->Filters;
	}

protected:

	// Construct default subfilters
	void ConstructSubFilters();
};
