// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "CardDeckExporterJSON.generated.h"


class UCardDeckModel;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class DECKBUILDERDESKTOP_API UCardDeckExporterJSON : public UObject
{
	GENERATED_UCLASS_BODY()
	
public:
	bool ExportDeckModel(UCardDeckModel* DeckModel, FString& OutExportText);
};
