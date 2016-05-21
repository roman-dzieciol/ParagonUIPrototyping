
#include "DeckBuilderDesktop.h"
#include "CardsFunctionLibrary.h"
#include "DataTables/FStatData.h"
#include "Models/CardDeckModel.h"
#include "Models/CardDeckExporterJSON.h"
#include "Models/CardDeckImporterJSON.h"
#include "ParagonSaveGame.h"
#include "Kismet/GameplayStatics.h"


UCardModel* UCardsFunctionLibrary::ConstructCardModelFromCardData(const FCardData& CardData, UDataTable* StatDataTable)
{
	return UCardModel::ConstructFromCardData(CardData, StatDataTable);
}

UCardListModel* UCardsFunctionLibrary::ConstructCardListFromCardDataTable(UDataTable* CardDataTable, UDataTable* StatDataTable)
{
	return UCardListModel::ConstructCardListFromCardDataTable(CardDataTable, StatDataTable);
}

UCardListModel* UCardsFunctionLibrary::ConstructCardListWithCardsFrom(UCardListModel* AnotherCardList)
{
	return UCardListModel::ConstructCardListWithCardsFrom(AnotherCardList);
}

TArray<FStatData> UCardsFunctionLibrary::FilterableStatsData(TArray<FStatData> StatsData)
{
	TArray<FStatData> FilterableStats = StatsData.FilterByPredicate([=](const FStatData& StatData) {
		return !StatData.FilterGroup.IsEmpty();
	});


	FilterableStats.StableSort([=](const FStatData& LHS, const FStatData& RHS) {
		return LHS.FilterGroupIndex < RHS.FilterGroupIndex;
	});

	FilterableStats.StableSort([=](const FStatData& LHS, const FStatData& RHS) {
		return LHS.FilterGroup.Compare(RHS.FilterGroup) < 0;
	});

	return FilterableStats;
}

FName UCardsFunctionLibrary::MakeValidTableRowName(const FString& InString)
{
	return DataTableUtils::MakeValidName(InString);
}

UTexture2D* UCardsFunctionLibrary::LoadCardTextureNamed(const FString& CardName)
{
	FString TexturePath = FString::Printf(TEXT("/Game/Art/Cards/T_%s.T_%s"), *CardName, *CardName);
	return LoadObject<UTexture2D>(NULL, *TexturePath, NULL, LOAD_NoWarn, NULL);
}
