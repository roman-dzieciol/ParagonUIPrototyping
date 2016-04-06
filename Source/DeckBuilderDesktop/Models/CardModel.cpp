
#include "DeckBuilderDesktop.h"
#include "CardModel.h"

UCardModel::UCardModel(class FObjectInitializer const & ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool operator == (const UCardModel& LHS, const UCardModel& RHS)
{
	return LHS.CardName.EqualTo(RHS.CardName)
		&& LHS.Cost == RHS.Cost
		&& LHS.Type.EqualTo(RHS.Type)
		&& LHS.Affinity.EqualTo(RHS.Affinity)
		&& LHS.Rarity.EqualTo(RHS.Rarity)
		&& LHS.BaseStats == RHS.BaseStats
		&& LHS.MaxedStats == RHS.MaxedStats;
}

UCardModel* UCardModel::ConstructFromCardData(const FCardData& CardData, UDataTable* StatDataTable)
{
	auto CardModel = NewObject<UCardModel>(GetTransientPackage(), CardData.StaticStruct()->GetFName());
	CardModel->CardName = FText::FromString(CardData.CardName);
	CardModel->Cost = CardData.Cost;
	CardModel->Type = FText::FromString(CardData.Type);
	CardModel->Affinity = FText::FromString(CardData.Affinity);
	CardModel->Rarity = FText::FromString(CardData.Rarity);
	CardModel->BaseStats = UCardStatModel::ConstructModelsFromCardData(CardData, TEXT("Base"), StatDataTable);
	CardModel->MaxedStats = UCardStatModel::ConstructModelsFromCardData(CardData, TEXT("Maxed"), StatDataTable);
	return CardModel;
}
