#pragma once

#include "UObject.h"
#include "Engine/Texture2D.h"
#include "CardStatModel.generated.h"

UCLASS(Blueprintable, BlueprintType)
class DECKBUILDERDESKTOP_API UCardStatModel : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Stat Model")
		FText Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Stat Model")
		FText Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Stat Model")
		UTexture2D* Icon;

	friend bool operator==(const UCardStatModel& LHS, const UCardStatModel& RHS);
};
