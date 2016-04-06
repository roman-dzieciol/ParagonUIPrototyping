
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
		&& LHS.Stats == RHS.Stats;
}
