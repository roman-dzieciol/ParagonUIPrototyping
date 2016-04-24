
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
	if (Filter == nullptr)
	{
		FilterStates.SetNumZeroed(AllCards.Num());
		return;
	}

	auto StateIt = FilterStates.CreateIterator();
	for (auto CardModel : AllCards)
	{
		*StateIt++ = Filter->IsMatching(CardModel) == false;
	}
}


void UCardListModel::ConstructDefaultFilters()
{
	UCardFilterGroup* MainFilter = NewObject<UCardFilterGroup>(GetTransientPackage(), NAME_None);
	MainFilter->Matching = ECardFilterGroupMatching::All;
	this->MainFilter = MainFilter;
	Filter = MainFilter;

	UCardFilterGroup* AffinityFilter = NewObject<UCardFilterGroup>(GetTransientPackage(), NAME_None);
	AffinityFilter->Matching = ECardFilterGroupMatching::Any;
	this->AffinityFilter = AffinityFilter;
	MainFilter->Filters.Add(AffinityFilter);

	UCardFilterGroup* UserFilter = NewObject<UCardFilterGroup>(GetTransientPackage(), NAME_None);
	UserFilter->Matching = ECardFilterGroupMatching::All;
	this->UserFilter = UserFilter;
	MainFilter->Filters.Add(UserFilter);

	TextFilter = UCardFilterByStat::ConstructCardFilterByStat(FName(TEXT("Text")), TEXT("CardName"), FString(), false);
}


UCardFilter* UCardListModel::SetAffinityFilters(TArray<FString> AffinityNames)
{
	check(AffinityFilter != nullptr);

	AffinityFilter->Filters.Empty();
	for (auto AffinityName : AffinityNames)
	{
		AffinityFilter->Filters.Add(UCardFilterByStat::ConstructCardFilterByStat(FName(TEXT("Affinity")), TEXT("Affinity"), AffinityName, true));
	}
	return AffinityFilter;
}


UCardFilter* UCardListModel::FilterByText(const FString& Text)
{
	check(TextFilter != nullptr);
	check(UserFilter != nullptr);
	TextFilter->StatContains = Text;

	if (Text.IsEmpty())
	{
		UserFilter->Filters.Remove(TextFilter);
	}
	else
	{
		UserFilter->Filters.AddUnique(TextFilter);
	}
	return TextFilter;
}


UCardFilter* UCardListModel::FilterByBaseStat(const FString& StatName)
{
	check(UserFilter != nullptr);
	check(UserFilter != nullptr);


	RemoveFiltersMatching(FName(TEXT("Stat")), FText(), FText::FromString(StatName));

	UCardFilterByStat* StatFilter = UCardFilterByStat::ConstructCardFilterByStat(FName(TEXT("Stat")), StatName, FString(), true);
	StatFilter->LocalizedValue = FText::FromString(StatName);
	UserFilter->Filters.Add(StatFilter);
	return StatFilter;
}

void UCardListModel::FilterByCostValues(const TArray<int32> CostValues)
{
	check(UserFilter != nullptr);
	check(UserFilter->IsValidLowLevel());

	RemoveFiltersMatching(FName(TEXT("Cost")), FText(), FText());
	for (auto CostValue : CostValues)
	{
		UserFilter->Filters.Add(UCardFilterFactory::ConstructFilterByCostValue(CostValue));
	}
}

TArray<UCardFilter*> UCardListModel::GetCostValueFilters() const 
{
	return FindFiltersMatching(FName(TEXT("Cost")), FText(), FText());
}

UCardFilter* UCardListModel::FilterBySlot(const FString& SlotName)
{
	check(UserFilter != nullptr);
	
	if (SlotFilter != nullptr)
	{
		UserFilter->Filters.Remove(SlotFilter);
		SlotFilter = nullptr;
	}

	if (SlotName.Equals(TEXT("Equipment")))
	{
		UCardFilterByStat* ActiveFilter =  UCardFilterByStat::ConstructCardFilterByStat(FName(TEXT("Slot")), TEXT("Type"), TEXT("Active"), true);
		UCardFilterByStat* PassiveFilter = UCardFilterByStat::ConstructCardFilterByStat(FName(TEXT("Slot")), TEXT("Type"), TEXT("Passive"), true);

		UCardFilterGroup* SlotOrFilter = NewObject<UCardFilterGroup>(GetTransientPackage(), NAME_None);
		SlotOrFilter->Matching = ECardFilterGroupMatching::Any;
		SlotOrFilter->FilterName = FName(TEXT("Slot"));
		SlotOrFilter->LocalizedName = FText::FromString(TEXT("Slot"));
		SlotOrFilter->LocalizedValue = FText::FromString(TEXT("Equipment"));
		SlotOrFilter->Filters.Add(ActiveFilter);
		SlotOrFilter->Filters.Add(PassiveFilter);
		this->SlotFilter = SlotOrFilter;
		UserFilter->Filters.Add(SlotOrFilter);
		return SlotOrFilter;
	}
	else
	{
		UCardFilterByStat* SlotFilter = UCardFilterByStat::ConstructCardFilterByStat(FName(TEXT("Slot")), TEXT("Type"), SlotName, true);
		SlotFilter->LocalizedName = FText::FromString(TEXT("Slot"));
		SlotFilter->LocalizedValue = FText::FromString(SlotName);
		this->SlotFilter = SlotFilter;
		UserFilter->Filters.Add(SlotFilter);
		return SlotFilter;
	}
}

void UCardListModel::RemoveFiltersMatching(FName TypeName, FText DisplayName, FText DisplayValue)
{
	UserFilter->RemoveFiltersMatching(TypeName, DisplayName, DisplayValue);
}

void UCardListModel::RemoveAllFilters()
{
	UserFilter->Filters.Empty();
}

void UCardListModel::RemoveFilter(UCardFilter* FilterToRemove)
{
	UserFilter->RemoveFilter(FilterToRemove);
}

TArray<UCardFilter*> UCardListModel::FindFiltersMatching(FName TypeName, FText DisplayName, FText DisplayValue) const
{
	return UserFilter->FindFiltersMatching(TypeName, DisplayName, DisplayValue);
}


