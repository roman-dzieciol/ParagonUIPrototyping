#pragma once

#include "UObject.h"
#include "Engine/DataTable.h"
#include "Filters/CardFilter.h"
#include "Filters/CardFilterGroup.h"
#include "Filters/CardFilterByStat.h"
#include "CardModel.h"
#include "CardListModel.generated.h"

UCLASS(Blueprintable, BlueprintType)
class DECKBUILDERDESKTOP_API UCardListModel : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card List")
	TArray<UCardModel*> AllCards;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card List")
	TArray<bool> FilterStates;

public:

	static UCardListModel* ConstructCardListFromCardDataTable(UDataTable* CardDataTable, UDataTable* StatDataTable);

public:

	UFUNCTION(BlueprintCallable, Category = "Card List")
		virtual void FilterCards();

	UFUNCTION(BlueprintCallable, Category = "Card List")
		UCardFilter* SetAffinityFilters(TArray<FString> AffinityNames);

	UFUNCTION(BlueprintCallable, Category = "Card List")
		UCardFilter* FilterByText(const FString& Text);

	UFUNCTION(BlueprintCallable, Category = "Card List")
		UCardFilter* FilterByBaseStat(const FString& StatName);

	UFUNCTION(BlueprintCallable, Category = "Card List")
		void FilterByCostValues(const TArray<int32> CostValues);

	UFUNCTION(BlueprintCallable, Category = "Card List")
		TArray<UCardFilter*> GetCostValueFilters() const;


	UFUNCTION(BlueprintCallable, Category = "Card List")
		UCardFilter* FilterBySlot(const FString& SlotName);

	UFUNCTION(BlueprintCallable, Category = "Card List")
		UCardFilter* GetSlotFilter() const;


	UFUNCTION(BlueprintCallable, Category = "Card List")
		void RemoveFiltersMatching(FName TypeName, FText DisplayName, FText DisplayValue);

	UFUNCTION(BlueprintCallable, Category = "Card List")
		void RemoveAllFilters();

	UFUNCTION(BlueprintCallable, Category = "Card List")
		void RemoveFilter(UCardFilter* FilterToRemove);

	UFUNCTION(BlueprintCallable, Category = "Card List")
		TArray<UCardFilter*> FindFiltersMatching(FName TypeName, FText DisplayName, FText DisplayValue) const;

protected: // Filter groups

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card List")
		UCardFilterGroup* RootFilterGroup;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card List")
		UCardFilterGroup* UserFilterGroup;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card List")
		UCardFilterGroup* AffinityFilterGroup;

protected: // User filters

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card List")
		UCardFilterGroup* SlotFilterGroup;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card List")
		UCardFilterByStat* TextFilter;

protected:

	void ConstructDefaultFilters();

};
