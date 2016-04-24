// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Filters/CardFilter.h"
#include "CardFilterByStat.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class DECKBUILDERDESKTOP_API UCardFilterByStat : public UCardFilter
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Filter")
		FString StatName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Filter")
		FString StatContains;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Filter")
		bool bEqualValue;

	UFUNCTION(BlueprintCallable, Category = "Card Filter by Stat")
		static UCardFilterByStat* ConstructCardFilterByStat(FName InFilterType, FString InStatName, FString InStatValue, bool InIsEqualValue);

	virtual bool IsMatching(UCardModel* CardModel) const override;

	virtual FText GetDisplayName() const override;
	virtual FText GetDisplayValue() const override;
	virtual TArray<UCardFilter*> FindFiltersMatching(FName MatchFilterName, FText MatchDisplayName, FText MatchDisplayValue) const override;
};
