#pragma once

#include "UObject.h"
#include "Engine/DataTable.h"
#include "Filters/CardFilterMain.h"
#include "CardModel.h"
#include "CardListModel.generated.h"

UCLASS(Blueprintable, BlueprintType)
class DECKBUILDERDESKTOP_API UCardListModel : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card List")
	TArray<UCardModel*> AllCards;

public:

	// Named constructor
	static UCardListModel* ConstructCardListFromCardDataTable(UDataTable* CardDataTable, UDataTable* StatDataTable);

public:

	// The main filter group
	UPROPERTY()
	UCardFilterMain* RootFilterGroup;
	
	// The results of filtering
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card List")
	TArray<bool> FilterStates;

	UFUNCTION(BlueprintCallable, Category = "Card List")
	UCardFilterMain* GetMainFilter() const
	{
		return RootFilterGroup;
	}

	UFUNCTION(BlueprintCallable, Category = "Card List")
	virtual void FilterCards();

};
