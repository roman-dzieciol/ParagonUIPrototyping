
#include "DeckBuilderDesktop.h"
#include "FHeroData.h"

bool operator == (const FHeroData& LHS, const FHeroData& RHS)
{
	return LHS.HeroID.Equals(RHS.HeroID);
}
