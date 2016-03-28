// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "FCardData.h"
#include "CardsDataFilter.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class DECKBUILDERDESKTOP_API UCardsDataFilter : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cards Data Filter")
	FName TypeName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cards Data Filter")
	FString PropertyString;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cards Data Filter")
	FString ValueString;
	
	UFUNCTION(BlueprintCallable, Category = "Cards Data Filter")
	virtual TArray<FCardData> FilteredCardsData(TArray<FCardData> CardsData);

	UFUNCTION(BlueprintCallable, Category = "Cards Data Filter")
	virtual bool IsActive();
};
