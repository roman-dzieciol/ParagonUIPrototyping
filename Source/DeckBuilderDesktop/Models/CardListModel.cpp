
#include "DeckBuilderDesktop.h"
#include "CardListModel.h"

UCardListModel::UCardListModel(class FObjectInitializer const & ObjectInitializer)
	: Super(ObjectInitializer)
{
}

TArray<UCardModel*> UCardListModel::LoadCardsFromDataTable(UDataTable* CardDataTable, UDataTable* StatDataTable)
{
	AllCards.Empty();

	if (CardDataTable == nullptr || StatDataTable == nullptr)
	{
		return AllCards;
	}

	for (auto RowName: CardDataTable->GetRowNames())
	{
		auto Row = CardDataTable->FindRow<FCardData>(RowName, TEXT(" UCardListModel::LoadCardsFromDataTable"));
		if (Row != nullptr)
		{
			auto CardModel = UCardModel::ConstructFromCardData(*Row, StatDataTable);
			if (CardModel != nullptr)
			{
				AllCards.Add(CardModel);
			}
		}
	}
	return AllCards;
}

