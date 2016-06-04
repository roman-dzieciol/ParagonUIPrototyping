// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "GameTypeListModel.generated.h"

class UGameTypeModel;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class DECKBUILDERDESKTOP_API UGameTypeListModel : public UObject
{
	GENERATED_UCLASS_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game Type List")
		TArray<UGameTypeModel*> GameTypeModels;

public:
	static UGameTypeListModel* ConstructFromGameTypeDataTable(UDataTable* GameTypeDataTable);
};
