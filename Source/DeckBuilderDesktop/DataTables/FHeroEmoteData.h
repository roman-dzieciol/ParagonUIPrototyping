#pragma once

#include "Engine/DataTable.h"
#include "FHeroEmoteData.generated.h"

USTRUCT(BlueprintType)
struct FHeroEmoteData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	FHeroEmoteData()
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Emote")
		FName ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Emote")
		FString Title;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Emote")
		FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Emote")
		UTexture2D* Icon;

	friend bool operator==(const FHeroEmoteData& LHS, const FHeroEmoteData& RHS);
};
