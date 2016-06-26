// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "RewardModel.h"
#include "DataTables/FStoreProductData.h"
#include "StoreProductModel.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class DECKBUILDERDESKTOP_API UStoreProductModel : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Store Product")
		FName ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Store Product")
		FString Title;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Store Product")
		FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Store Product")
		FString Tooltip;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Store Product")
		int32 Price;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Store Product")
		FName Currency;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Store Product")
		TAssetPtr<class UTexture2D> Icon;

public:
	static UStoreProductModel* ConstructFromStoreProductData(const FStoreProductData& StoreProductData);
	
	
};
