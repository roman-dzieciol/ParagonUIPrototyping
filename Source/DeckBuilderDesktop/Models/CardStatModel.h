#pragma once

#include "UObject.h"
#include "Engine/DataTable.h"
#include "Engine/Texture2D.h"
#include "DataTables/FStatData.h"
#include "DataTables/FCardData.h"
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
		FText BonusType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Stat Model")
		UTexture2D* Icon;


	static UCardStatModel* ConstructWithName(const FName& StatName, const FText& Value, const FStatData& StatData);

	static UCardStatModel* ConstructFromProperty(UProperty* Property, void const * Container, const FStatData& StatData);

	static TArray<UCardStatModel*> ConstructModelsFromCardData(const FCardData& CardData, const FString& BonusType, UDataTable* StatDataTable);

	friend bool operator==(const UCardStatModel& LHS, const UCardStatModel& RHS);
};
