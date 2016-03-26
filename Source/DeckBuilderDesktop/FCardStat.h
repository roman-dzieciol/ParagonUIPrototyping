#pragma once

#include "FCardStat.generated.h"

USTRUCT(BlueprintType)
struct FCardStat {

	GENERATED_USTRUCT_BODY()

public:

	FCardStat() {

	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
		FName Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
		FString Value;
};