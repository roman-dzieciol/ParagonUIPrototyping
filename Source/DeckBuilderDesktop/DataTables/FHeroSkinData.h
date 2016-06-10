#pragma once

#include "Engine/DataTable.h"
#include "FHeroSkinData.generated.h"

USTRUCT(BlueprintType)
struct FHeroSkinData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FHeroSkinData(){}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Skin Data")
		FString SkinName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Skin Data")
		UTexture2D* IconTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Skin Data")
		TAssetPtr<class UTexture2D> PreviewTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Skin Data")
		FString Title;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Skin Data")
		FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Skin Data")
		int32 Cost;

	friend bool operator==(const FHeroSkinData& LHS, const FHeroSkinData& RHS);
};

