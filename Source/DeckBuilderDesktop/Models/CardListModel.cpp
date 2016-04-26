
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
	RootFilterGroup = UCardFilterMain::ConstructCardFilterMain(FName(TEXT("MainGroup")), ECardFilterGroupMatching::All);

	// User filters, configured by user
	UserFilterGroup = UCardFilterGroup::ConstructCardFilterGroup(FName(TEXT("UserGroup")), ECardFilterGroupMatching::All);
	RootFilterGroup->AddFilter(UserFilterGroup);
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
	check(RootFilterGroup->TextFilter != nullptr);
	check(RootFilterGroup->TextFilter->IsValidLowLevel());

	TArray<UCardFilter*> DisplayableFilters;
	DisplayableFilters.Append(UserFilterGroup->Filters);

	if (!RootFilterGroup->TextFilter->StatContains.IsEmpty())
	{
		DisplayableFilters.Add(RootFilterGroup->TextFilter);
	}
	return DisplayableFilters;
}

