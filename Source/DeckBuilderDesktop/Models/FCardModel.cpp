
#include "DeckBuilderDesktop.h"
#include "FCardModel.h"

bool operator == (const FCardModel& LHS, const FCardModel& RHS)
{
	return LHS.CardName == RHS.CardName
		&& LHS.Cost == RHS.Cost
		&& LHS.Type == RHS.Type
		&& LHS.Affinity == RHS.Affinity
		&& LHS.Rarity == RHS.Rarity
		&& LHS.Stats == RHS.Stats;
}
