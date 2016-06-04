#pragma once

#include "Engine/DataTable.h"
#include "FGameTypeData.generated.h"

USTRUCT(BlueprintType)
struct FGameTypeData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FGameTypeData(){}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Type Data")
		FString GameTypeName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Type Data")
		FString Title;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Type Data")
		FString Description;

	friend bool operator==(const FGameTypeData& LHS, const FGameTypeData& RHS);
};

