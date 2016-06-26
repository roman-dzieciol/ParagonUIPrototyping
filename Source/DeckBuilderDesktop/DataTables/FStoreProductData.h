#pragma once

#include "Engine/DataTable.h"
#include "FStoreProductData.generated.h"

USTRUCT(BlueprintType)
struct FStoreProductData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	FStoreProductData()
	{}

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

	friend bool operator==(const FStoreProductData& LHS, const FStoreProductData& RHS);
};
