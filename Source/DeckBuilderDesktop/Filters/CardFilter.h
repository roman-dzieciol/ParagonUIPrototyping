// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Models/CardModel.h"
#include "CardFilter.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class DECKBUILDERDESKTOP_API UCardFilter : public UObject
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Filter")
	FName FilterName;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Filter")
		FText LocalizedName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Filter")
		FText LocalizedValue;

	
public:
	virtual bool IsMatching(UCardModel* CardModel) const;

	UFUNCTION(BlueprintCallable, Category = "Card Filter")
	virtual FText GetDisplayName() const;

	UFUNCTION(BlueprintCallable, Category = "Card Filter")
	virtual FText GetDisplayValue() const;

	virtual void RemoveFiltersMatching(FName FilterName, FText DisplayName, FText DisplayValue);

	virtual void RemoveFilter(UCardFilter* FilterToRemove);
	
};
