#pragma once

#include "Engine/DataTable.h"
#include "FHeroData.generated.h"

USTRUCT(BlueprintType)
struct FHeroData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FHeroData(){}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Data")
		FText HeroName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Data")
		UTexture2D* AvatarTexture;

	friend bool operator==(const FHeroData& LHS, const FHeroData& RHS);
};

