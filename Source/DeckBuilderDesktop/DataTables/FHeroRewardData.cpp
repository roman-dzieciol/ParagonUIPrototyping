
#include "DeckBuilderDesktop.h"
#include "FHeroRewardData.h"

bool operator == (const FHeroRewardData& LHS, const FHeroRewardData& RHS)
{
	return LHS.ID == RHS.ID;
}
