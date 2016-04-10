
#include "DeckBuilderDesktop.h"
#include "CardListModel.h"

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
		UE_LOG(Deck, Log, TEXT("LoadCardsFromDataTable: %s"), *RowName.ToString());
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

	UCardFilterByStat* TextFilter = NewObject<UCardFilterByStat>(GetTransientPackage(), NAME_None);
	this->TextFilter = TextFilter;
	TextFilter->FilterName = FName(TEXT("Text"));
	TextFilter->StatName = TEXT("CardName");
}


UCardFilter* UCardListModel::SetAffinityFilters(TArray<FString> AffinityNames)
{
	check(AffinityFilter != nullptr);

	AffinityFilter->Filters.Empty();
	for (auto AffinityName : AffinityNames)
	{
		UCardFilterByStat* StatFilter = NewObject<UCardFilterByStat>(GetTransientPackage(), NAME_None);
		StatFilter->FilterName = FName(TEXT("Affinity"));
		StatFilter->StatName = TEXT("Affinity");
		StatFilter->StatContains = AffinityName;
		AffinityFilter->Filters.Add(StatFilter);
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

	UCardFilterByStat* StatFilter = NewObject<UCardFilterByStat>(GetTransientPackage(), NAME_None);
	StatFilter->FilterName = FName(TEXT("Stat"));
	StatFilter->StatName = StatName;
	StatFilter->LocalizedValue = FText::FromString(StatName);
	UserFilter->Filters.Add(StatFilter);
	return StatFilter;
}

UCardFilter* UCardListModel::FilterByCost(const int32 CostValue)
{
	check(UserFilter != nullptr);

	RemoveFiltersMatching(FName(TEXT("Cost")), FText(), FText());

	UCardFilterByStat* CostFilter = NewObject<UCardFilterByStat>(GetTransientPackage(), NAME_None);
	CostFilter->FilterName = FName(TEXT("Cost"));
	CostFilter->StatName = TEXT("Cost");
	CostFilter->StatContains = FString::FromInt(CostValue);
	CostFilter->bEqualValue = true;
	UserFilter->Filters.Add(CostFilter);
	return CostFilter;
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
		UCardFilterByStat* ActiveFilter = NewObject<UCardFilterByStat>(GetTransientPackage(), NAME_None);
		ActiveFilter->FilterName = FName(TEXT("Slot"));
		ActiveFilter->StatName = TEXT("Type");
		ActiveFilter->StatContains = TEXT("Active");
		ActiveFilter->bEqualValue = true;

		UCardFilterByStat* PassiveFilter = NewObject<UCardFilterByStat>(GetTransientPackage(), NAME_None);
		PassiveFilter->FilterName = FName(TEXT("Slot"));
		PassiveFilter->StatName = TEXT("Type");
		PassiveFilter->StatContains = TEXT("Passive");
		PassiveFilter->bEqualValue = true;

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
		UCardFilterByStat* SlotFilter = NewObject<UCardFilterByStat>(GetTransientPackage(), NAME_None);
		SlotFilter->FilterName = FName(TEXT("Slot"));
		SlotFilter->LocalizedName = FText::FromString(TEXT("Slot"));
		SlotFilter->LocalizedValue = FText::FromString(SlotName);
		SlotFilter->StatName = TEXT("Type");
		SlotFilter->StatContains = SlotName;
		SlotFilter->bEqualValue = true;
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


