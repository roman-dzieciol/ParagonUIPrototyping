#pragma once

#include "Engine/DataTable.h"
#include "Engine/Texture2D.h"
#include "FCardStatIconData.generated.h"

/** Structure that defines a level up table entry */
USTRUCT(BlueprintType)
struct FCardStatIconData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	FCardStatIconData()
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = IconData)
		UTexture2D* Icon;

};
