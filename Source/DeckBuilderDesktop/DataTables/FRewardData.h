#pragma once

#include "Engine/DataTable.h"
#include "FRewardData.generated.h"

USTRUCT(BlueprintType)
struct FRewardData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	FRewardData()
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Daily Reward")
		FString RewardName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Daily Reward")
		FString RewardType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Daily Reward")
		FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Daily Reward")
		UTexture2D* Icon;

	friend bool operator==(const FRewardData& LHS, const FRewardData& RHS);
};
