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
		FString HeroID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Data")
		FString HeroName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Data")
		UTexture2D* AvatarTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Data")
		TArray<FString> Affinities;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Data")
		TArray<FString> RecommendedStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Data")
		TArray<FString> NotRecommendedStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Data")
		TArray<FString> Abilities;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Data")
		TArray<FString> Skins;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Data")
		FString Difficulty;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Data")
		int32 BasicAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Data")
		int32 AbilityPower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Data")
		int32 Durability;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Data")
		int32 Mobility;

	friend bool operator==(const FHeroData& LHS, const FHeroData& RHS);
};

