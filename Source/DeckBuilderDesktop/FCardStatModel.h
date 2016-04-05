#pragma once

#include "Engine/Texture2D.h"
#include "FCardStatModel.generated.h"

USTRUCT(BlueprintType)
struct FCardStatModel {

	GENERATED_USTRUCT_BODY()

public:

	FCardStatModel() {

	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Stat")
		FName Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Stat")
		FString Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Stat")
		UTexture2D* Icon;
};
