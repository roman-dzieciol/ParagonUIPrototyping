#pragma once
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#pragma once

#include "DataTables/FCardData.h"
#include "Models/CardModel.h"
#include "Models/CardStatModel.h"
#include "CardsFunctionLibrary.generated.h"


UCLASS()
class UCardsFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Card Model")
	static TArray<UCardStatModel*> ConstructExistingCardStatModelsFromTableData(const FCardData& CardData);

	UFUNCTION(BlueprintCallable, Category = "Card Model")
	static UCardModel* ConstructCardModelFromTableData(const FCardData& CardData);
};

