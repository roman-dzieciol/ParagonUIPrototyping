#pragma once

#include "UObject.h"
#include "Engine/Texture2D.h"
#include "CardStatModel.h"
#include "CardModel.generated.h"

UCLASS(Blueprintable, BlueprintType)
class DECKBUILDERDESKTOP_API UCardModel : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Model")
		FText CardName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Model")
		int32 Cost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Model")
		FText Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Model")
		FText Affinity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Model")
		FText Rarity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Model")
		TArray<UCardStatModel*> Stats;

	friend bool operator==(const UCardModel& LHS, const UCardModel& RHS);
};
