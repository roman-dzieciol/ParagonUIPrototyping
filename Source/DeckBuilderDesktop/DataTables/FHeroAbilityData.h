#pragma once

#include "Engine/DataTable.h"
#include "FHeroAbilityData.generated.h"

USTRUCT(BlueprintType)
struct FHeroAbilityData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FHeroAbilityData(){}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Ability Data")
		FString AbilityName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Ability Data")
		FString Title;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Ability Data")
		FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Ability Data")
		TArray<float> ManaCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Ability Data")
		TArray<float> Cooldown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Ability Data")
		UTexture2D* IconTexture;

	friend bool operator==(const FHeroAbilityData& LHS, const FHeroAbilityData& RHS);
};

