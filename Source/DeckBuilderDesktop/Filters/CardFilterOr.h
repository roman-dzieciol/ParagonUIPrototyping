// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Filters/CardFilter.h"
#include "CardFilterOr.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class DECKBUILDERDESKTOP_API UCardFilterOr : public UCardFilter
{
	GENERATED_UCLASS_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Filter")
	TArray<UCardFilter*> Filters;

	virtual bool IsMatching(UCardModel* CardModel) const override;
	virtual void RemoveFiltersMatching(FName FilterName, FText DisplayName, FText DisplayValue) override;
	virtual void RemoveFilter(UCardFilter* FilterToRemove) override;
};
