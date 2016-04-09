
#include "DeckBuilderDesktop.h"
#include "CardsFunctionLibrary.h"
#include "DataTables/FStatData.h"


UCardModel* UCardsFunctionLibrary::ConstructCardModelFromCardData(const FCardData& CardData, UDataTable* StatDataTable)
{
	return UCardModel::ConstructFromCardData(CardData, StatDataTable);
}

UCardListModel* UCardsFunctionLibrary::ConstructCardListFromCardDataTable(UDataTable* CardDataTable, UDataTable* StatDataTable)
{
	return UCardListModel::ConstructCardListFromCardDataTable(CardDataTable, StatDataTable);
}