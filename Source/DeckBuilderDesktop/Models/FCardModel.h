#pragma once

#include "Engine/Texture2D.h"
#include "FCardStatModel.h"
#include "FCardModel.generated.h"

USTRUCT(BlueprintType)
struct FCardModel {

	GENERATED_USTRUCT_BODY()

public:

	FCardModel() {

	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Card)
		FString CardName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Card)
		float Cost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Card)
		FString Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Card)
		FString Affinity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Card)
		FString Rarity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Card)
		TArray<FCardStatModel> Stats;

	friend bool operator==(const FCardModel& LHS, const FCardModel& RHS);
};
