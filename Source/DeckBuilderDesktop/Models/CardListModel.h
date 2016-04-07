#pragma once

#include "UObject.h"
#include "Engine/DataTable.h"
#include "CardModel.h"
#include "CardListModel.generated.h"

UCLASS(Blueprintable, BlueprintType)
class DECKBUILDERDESKTOP_API UCardListModel : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card List")
	TArray<UCardModel*> AllCards;
	
	UFUNCTION(BlueprintCallable, Category = "Card List")
	virtual TArray<UCardModel*> LoadCardsFromDataTable(UDataTable* CardDataTable, UDataTable* StatDataTable);
};
