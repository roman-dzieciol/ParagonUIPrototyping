#pragma once

#include "UObject.h"
#include "Engine/DataTable.h"
#include "Filters/CardFilterMain.h"
#include "CardModel.h"
#include "CardListModel.generated.h"

// Holds a list of all card models and the card filters
UCLASS(Blueprintable, BlueprintType)
class DECKBUILDERDESKTOP_API UCardListModel : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	// List of all card models
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
	// Always matches the AllCards property
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card List")
	TArray<bool> FilterStates;

	// The main filter public accessor for Blueprints
	UFUNCTION(BlueprintCallable, Category = "Card List")
	UCardFilterMain* GetMainFilter() const
	{
		return RootFilterGroup;
	}

	// Filter cards in the AllCards property using the RootFilterGroup.
	// Stores results in the FilterStates property
	UFUNCTION(BlueprintCallable, Category = "Card List")
	virtual void FilterCards();

};
