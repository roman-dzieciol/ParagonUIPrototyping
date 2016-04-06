// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#pragma once

#include "DataTables/FCardStat.h"
#include "DataTables/FCardData.h"
#include "Filters/CardsDataFilter.h"
#include "DataTables/FStatData.h"
#include "Models/FCardModel.h"
#include "CardBlueprintLibrary.generated.h"


UCLASS()
class UCardBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "CardStat Query")
	static TArray<FCardStat> GetValidCardStats(FCardData CardData);

	UFUNCTION(BlueprintCallable, Category = "CardData")
	static TArray<FCardData> CardsDataContainingProperty(TArray<FCardData> CardsData, FName PropertyName);

	UFUNCTION(BlueprintCallable, Category = "CardData")
	static TArray<FCardData> CardsDataContainingPropertyValue(TArray<FCardData> CardsData, FName PropertyName, FString PropertyValue);

	UFUNCTION(BlueprintCallable, Category = "CardData")
	static TArray<FCardData> CardsDataWithCardType(TArray<FCardData> CardsData, FString CardType);

	UFUNCTION(BlueprintCallable, Category = "CardData")
	static TArray<FCardData> CardsDataWithCardNameSubstring(TArray<FCardData> CardsData, FString Substring);

	UFUNCTION(BlueprintCallable, Category = "StatData")
	static TArray<FStatData> FilterableStatsData(TArray<FStatData> StatsData);

	UFUNCTION(BlueprintCallable, Category = "TableRow")
	static FName MakeValidTableRowName(const FString& InString);

	UFUNCTION(BlueprintCallable, Category = "Card Art")
	static UTexture2D* LoadCardTextureNamed(const FString& CardName);

};

