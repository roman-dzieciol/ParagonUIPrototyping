// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Filters/CardFilter.h"
#include "CardFilterFactory.generated.h"

/**
 * 
 */
UCLASS()
class DECKBUILDERDESKTOP_API UCardFilterFactory : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Card Model")
		static UCardFilter* ConstructFilterByCostValue(int32 CostValue);
};
