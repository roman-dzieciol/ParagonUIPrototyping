
#include "DeckBuilderDesktop.h"
#include "CardListModel.h"
#include "Blueprints/CardFilterFactory.h"

UCardListModel::UCardListModel(class FObjectInitializer const & ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Root filter group
	RootFilterGroup = UCardFilterMain::ConstructCardFilterMain(FName(TEXT("MainGroup")), ECardFilterGroupMatching::All);
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
	return CardListModel;
}

UCardListModel* UCardListModel::ConstructCardListWithCardsFrom(UCardListModel* AnotherCardList)
{
	auto CardListModel = NewObject<UCardListModel>(GetTransientPackage(), NAME_None);
	CardListModel->AllCards.Append(AnotherCardList->AllCards);
	CardListModel->FilterStates.SetNumZeroed(CardListModel->AllCards.Num());
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

TArray<UCardModel*> UCardListModel::GetFilteredCards()
{
	FilterCards();
	TArray<UCardModel*> FilteredCards;
	auto StateIt = FilterStates.CreateIterator();
	for (auto CardModel : AllCards)
	{
		if (*StateIt++ == false) 
		{
			FilteredCards.Add(CardModel);
		}
	}
	return FilteredCards;
}
