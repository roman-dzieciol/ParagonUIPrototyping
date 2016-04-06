#pragma once
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#pragma once

#include "DataTables/FCardData.h"
#include "Engine/DataTable.h"
#include "Models/CardModel.h"
#include "CardsFunctionLibrary.generated.h"


UCLASS()
class UCardsFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Card Model")
	static UCardModel* ConstructCardModelFromCardData(const FCardData& CardData, UDataTable* StatDataTable);
};

