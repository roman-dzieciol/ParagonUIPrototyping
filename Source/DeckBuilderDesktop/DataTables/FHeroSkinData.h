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
		FString Title;

	friend bool operator==(const FHeroSkinData& LHS, const FHeroSkinData& RHS);
};

