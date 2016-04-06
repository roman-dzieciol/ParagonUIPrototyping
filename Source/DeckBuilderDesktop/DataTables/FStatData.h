#pragma once

#include "Engine/DataTable.h"
#include "FStatData.generated.h"

USTRUCT(BlueprintType)
struct FStatData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	FStatData()
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Card)
		FString StatName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Card)
		FString FilterGroup;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Card)
		int32 FilterGroupIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Card)
		FString BonusType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Card)
		UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Card)
		FString Reserved;

	friend bool operator==(const FStatData& LHS, const FStatData& RHS);
};

