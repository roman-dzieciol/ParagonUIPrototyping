// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Engine/DataTable.h"
#include "DataTables/FGameTypeData.h"
#include "GameTypeModel.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class DECKBUILDERDESKTOP_API UGameTypeModel : public UObject
{
	GENERATED_UCLASS_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Type")
		FString GameTypeName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Type")
		FString Title;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Type")
		FString Description;
	
public:
	static UGameTypeModel* ConstructFromGameTypeData(const FGameTypeData& GameTypeData);
	
};
