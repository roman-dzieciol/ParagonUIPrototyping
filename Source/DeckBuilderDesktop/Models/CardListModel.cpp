
#include "DeckBuilderDesktop.h"
#include "CardListModel.h"
#include "Blueprints/CardFilterFactory.h"

UCardListModel::UCardListModel(class FObjectInitializer const & ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UCardListModel* UCardListModel::ConstructCardListFromCardDataTable(UDataTable* CardDataTable, UDataTable* StatDataTable)
{
	if (CardDataTable == nullptr || StatDataTable == nullptr)
	{
		return nullptr;
	}

	auto CardListModel = NewObject<UCardListModel>(GetTransientPackage(), NAME_None);

	for (auto RowName: CardDataTable->GetRowNames())
	{
		FCardData* Row = CardDataTable->FindRow<FCardData>(RowName, TEXT(" UCardListModel::LoadCardsFromDataTable"));
		if (Row != nullptr)
		{
			UCardModel* CardModel = UCardModel::ConstructFromCardData(*Row, StatDataTable);
			if (CardModel != nullptr)
			{
				CardListModel->AllCards.Add(CardModel);
			}
		}
	}
	CardListModel->FilterStates.SetNumZeroed(CardListModel->AllCards.Num());
	CardListModel->ConstructDefaultFilters();
	return CardListModel;
}

void UCardListModel::FilterCards()
{
	if (RootFilterGroup == nullptr)
	{
		FilterStates.SetNumZeroed(AllCards.Num());
		return;
	}

	auto StateIt = FilterStates.CreateIterator();
	for (auto CardModel : AllCards)
	{
		*StateIt++ = RootFilterGroup->IsMatching(CardModel) == false;
	}
}

void UCardListModel::ConstructDefaultFilters()
{
	// Root filter group
	RootFilterGroup = UCardFilterGroup::ConstructCardFilterGroup(FName(TEXT("MainGroup")), ECardFilterGroupMatching::All);

	// Deck affinity filters, configured by app
	AffinityFilterGroup = UCardFilterGroup::ConstructCardFilterGroup(FName(TEXT("AffinityGroup")), ECardFilterGroupMatching::Any);
	RootFilterGroup->AddFilter(AffinityFilterGroup);

	// User filters, configured by user
	UserFilterGroup = UCardFilterGroup::ConstructCardFilterGroup(FName(TEXT("UserGroup")), ECardFilterGroupMatching::All);
	RootFilterGroup->AddFilter(UserFilterGroup);

	// Search by text filter, configured by user
	TextFilter = UCardFilterByStat::ConstructCardFilterByStat(FName(TEXT("Text")), TEXT("CardName"), FString(), false);
	RootFilterGroup->AddFilter(TextFilter);
}

UCardFilter* UCardListModel::SetAffinityFilters(TArray<FString> AffinityNames)
{
	check(AffinityFilterGroup != nullptr);
	check(AffinityFilterGroup->IsValidLowLevel());
	UE_LOG(Deck, Verbose, TEXT("UCardListModel::FilterByCostValues: %s"), *FString::Join(AffinityNames, TEXT(", ")));

	AffinityFilterGroup->RemoveAllFilters();
	for (auto AffinityName : AffinityNames)
	{
		AffinityFilterGroup->AddFilter(UCardFilterByStat::ConstructCardFilterByStat(FName(TEXT("Affinity")), TEXT("Affinity"), AffinityName, false));
	}
	return AffinityFilterGroup;
}

UCardFilter* UCardListModel::FilterByText(const FString& Text)
{
	check(TextFilter != nullptr);
	check(TextFilter->IsValidLowLevel());
	UE_LOG(Deck, Verbose, TEXT("UCardListModel::FilterByText: %s"), *Text);
	TextFilter->StatContains = Text;
	return TextFilter;
}

UCardFilter* UCardListModel::GetTextFilter() const
{
	return TextFilter;
}

UCardFilter* UCardListModel::FilterByBaseStat(const FString& StatName)
{
	check(UserFilterGroup != nullptr);
	check(UserFilterGroup->IsValidLowLevel());
	UE_LOG(Deck, Verbose, TEXT("UCardListModel::FilterByBaseStat: %s"), *StatName);
	
	UCardFilterByStat* StatFilter = UCardFilterByStat::ConstructCardFilterByStat(FName(TEXT("Stat")), StatName, FString(), true);
	StatFilter->LocalizedValue = FText::FromString(StatName);
	UserFilterGroup->AddFilter(StatFilter);
	return StatFilter;
}

TArray<UCardFilter*> UCardListModel::GetBaseStatFilters() const
{
	return FindFiltersMatching(FName(TEXT("Stat")), FText(), FText());
}

void UCardListModel::FilterByCostValues(const TArray<int32> CostValues)
{
	check(UserFilterGroup != nullptr);
	check(UserFilterGroup->IsValidLowLevel());
	UE_LOG(Deck, Verbose, TEXT("UCardListModel::FilterByCostValues: %s"), *FString::Join(CostValues, TEXT(", ")));

	RemoveFiltersMatching(FName(TEXT("Cost")), FText(), FText());
	for (auto CostValue : CostValues)
	{
		UserFilterGroup->AddFilter(UCardFilterFactory::ConstructFilterByCostValue(CostValue));
	}
}

TArray<UCardFilter*> UCardListModel::GetCostValueFilters() const 
{
	return FindFiltersMatching(FName(TEXT("Cost")), FText(), FText());
}

UCardFilter* UCardListModel::FilterBySlot(const FString& SlotName)
{
	UE_LOG(Deck, Verbose, TEXT("UCardListModel::FilterBySlot: %s"), *SlotName);

	check(UserFilterGroup != nullptr);
	check(UserFilterGroup->IsValidLowLevel());

	SlotFilterGroup = UCardFilterGroup::ConstructCardFilterGroup(FName(TEXT("Slot")), ECardFilterGroupMatching::Any);
	SlotFilterGroup->LocalizedName = FText::FromString(TEXT("Slot"));
	SlotFilterGroup->LocalizedValue = FText::FromString(SlotName);
	UserFilterGroup->AddFilter(SlotFilterGroup);

	if (SlotName.Equals(TEXT("Equipment")))
	{
		SlotFilterGroup->AddFilter(UCardFilterByStat::ConstructCardFilterByStat(FName(TEXT("Slot")), TEXT("Type"), TEXT("Active"), true));
		SlotFilterGroup->AddFilter(UCardFilterByStat::ConstructCardFilterByStat(FName(TEXT("Slot")), TEXT("Type"), TEXT("Passive"), true));
	}
	else
	{
		SlotFilterGroup->AddFilter(UCardFilterByStat::ConstructCardFilterByStat(FName(TEXT("Slot")), TEXT("Type"), SlotName, true));
	}

	return SlotFilterGroup;
}

UCardFilter* UCardListModel::GetSlotFilter() const
{
	if (SlotFilterGroup != nullptr && SlotFilterGroup->IsValidLowLevel() && SlotFilterGroup->Parent != nullptr)
	{
		return SlotFilterGroup;
	}
	return nullptr;
}

void UCardListModel::RemoveFiltersMatching(FName TypeName, FText DisplayName, FText DisplayValue)
{
	check(UserFilterGroup != nullptr);
	check(UserFilterGroup->IsValidLowLevel());
	UserFilterGroup->RemoveFiltersMatching(TypeName, DisplayName, DisplayValue);
}

void UCardListModel::RemoveAllFilters()
{
	UserFilterGroup->RemoveAllFilters();
}

void UCardListModel::RemoveFilter(UCardFilter* FilterToRemove)
{
	check(FilterToRemove != nullptr);
	check(FilterToRemove->IsValidLowLevel());

	UE_LOG(Deck, Verbose, TEXT("UCardListModel::RemoveFilter: %s"), *FilterToRemove->ToString());

	if (FilterToRemove == TextFilter)
	{
		TextFilter->StatContains.Empty();
		return;
	}

	if (FilterToRemove == SlotFilterGroup)
	{
		SlotFilterGroup = nullptr;
	}

	FilterToRemove->RemoveThisFilter();
}

TArray<UCardFilter*> UCardListModel::FindFiltersMatching(FName TypeName, FText DisplayName, FText DisplayValue) const
{
	check(UserFilterGroup != nullptr);
	check(UserFilterGroup->IsValidLowLevel());

	return UserFilterGroup->FindFiltersMatching(TypeName, DisplayName, DisplayValue);
}

TArray<UCardFilter*> UCardListModel::GetDisplayableFilters() const
{
	check(UserFilterGroup != nullptr);
	check(UserFilterGroup->IsValidLowLevel());

	return UserFilterGroup->Filters;
}

