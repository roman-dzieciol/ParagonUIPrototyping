#pragma once

#include "Engine/DataTable.h"
#include "FHeroRewardData.generated.h"

USTRUCT(BlueprintType)
struct FHeroRewardData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	FHeroRewardData()
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Reward")
		FName ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Reward")
		FString Title;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Reward")
		FString Reward;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Reward")
		float MatchXPBoost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Reward")
		float MatchTeamXPBoost;

	friend bool operator==(const FHeroRewardData& LHS, const FHeroRewardData& RHS);
};
