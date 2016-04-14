// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Filters/CardFilter.h"
#include "CardFilterGroup.generated.h"


// Method of specifying polygons for a sprite's render or collision data
UENUM()
enum class ECardFilterGroupMatching : uint8
{
	/** Match only if all filters in group match the card */
	All,

	/** Match if any filter in group matches the card */
	Any
};


/**
*
*/
UCLASS(Blueprintable, BlueprintType)
class DECKBUILDERDESKTOP_API UCardFilterGroup : public UCardFilter
{
	GENERATED_UCLASS_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Filter")
	TArray<UCardFilter*> Filters;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Filter")
	ECardFilterGroupMatching Matching;

	virtual bool IsMatching(UCardModel* CardModel) const override;
	virtual void RemoveFiltersMatching(FName MatchFilterName, FText MatchDisplayName, FText MatchDisplayValue) override;
	virtual void RemoveFilter(UCardFilter* FilterToRemove) override;
	virtual TArray<UCardFilter*> FindFiltersMatching(FName MatchFilterName, FText MatchDisplayName, FText MatchDisplayValue) const override;
};
