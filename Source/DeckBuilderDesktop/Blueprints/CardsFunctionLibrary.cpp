
#include "DeckBuilderDesktop.h"
#include "CardsFunctionLibrary.h"
#include "DataTables/FStatData.h"


UCardModel* UCardsFunctionLibrary::ConstructCardModelFromCardData(const FCardData& CardData, UDataTable* StatDataTable)
{
	return UCardModel::ConstructFromCardData(CardData, StatDataTable);
}
