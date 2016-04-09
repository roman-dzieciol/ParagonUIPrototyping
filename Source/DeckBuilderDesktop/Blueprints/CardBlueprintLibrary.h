// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#pragma once

#include "DataTables/FStatData.h"
#include "CardBlueprintLibrary.generated.h"


UCLASS()
class UCardBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "StatData")
	static TArray<FStatData> FilterableStatsData(TArray<FStatData> StatsData);

	UFUNCTION(BlueprintCallable, Category = "TableRow")
	static FName MakeValidTableRowName(const FString& InString);

	UFUNCTION(BlueprintCallable, Category = "Card Art")
	static UTexture2D* LoadCardTextureNamed(const FString& CardName);
};

