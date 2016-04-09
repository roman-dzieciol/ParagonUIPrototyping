// Fill out your copyright notice in the Description page of Project Settings.

#include "DeckBuilderDesktop.h"
#include "CardBlueprintLibrary.h"

TArray<FStatData> UCardBlueprintLibrary::FilterableStatsData(TArray<FStatData> StatsData)
{
	TArray<FStatData> FilterableStats = StatsData.FilterByPredicate([=](const FStatData& StatData) {
		return !StatData.FilterGroup.IsEmpty();
	});


	FilterableStats.StableSort([=](const FStatData& LHS, const FStatData& RHS) {
		return LHS.FilterGroupIndex < RHS.FilterGroupIndex;
	});

	FilterableStats.StableSort([=](const FStatData& LHS, const FStatData& RHS) {
		return LHS.FilterGroup.Compare(RHS.FilterGroup) < 0;
	});

	return FilterableStats;
}

FName UCardBlueprintLibrary::MakeValidTableRowName(const FString& InString)
{
	return DataTableUtils::MakeValidName(InString);
}

UTexture2D* UCardBlueprintLibrary::LoadCardTextureNamed(const FString& CardName)
{
	FString TexturePath = FString::Printf(TEXT("/Game/Art/Cards/T_%s.T_%s"), *CardName, *CardName);
	return LoadObject<UTexture2D>(NULL, *TexturePath, NULL, LOAD_None, NULL);
}
