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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Filter")
		UCardFilter* Parent;
	
public:
	virtual bool IsMatching(UCardModel* CardModel) const;

	virtual FString ToString() const;

	UFUNCTION(BlueprintCallable, Category = "Card Filter")
	virtual FText GetDisplayName() const;

	UFUNCTION(BlueprintCallable, Category = "Card Filter")
	virtual FText GetDisplayValue() const;

	UFUNCTION(BlueprintCallable, Category = "Card Filter")
	virtual void RemoveFiltersMatching(FName MatchFilterName, FText MatchDisplayName, FText MatchDisplayValue);

	UFUNCTION(BlueprintCallable, Category = "Card Filter")
	virtual void RemoveFilter(UCardFilter* FilterToRemove);

	UFUNCTION(BlueprintCallable, Category = "Card Filter")
	virtual void RemoveThisFilter();

	UFUNCTION(BlueprintCallable, Category = "Card Filter")
	virtual TArray<UCardFilter*> FindFiltersMatching(FName MatchFilterName, FText MatchDisplayName, FText MatchDisplayValue) const;
};
