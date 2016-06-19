
#include "DeckBuilderDesktop.h"
#include "FHeroEmoteData.h"

bool operator == (const FHeroEmoteData& LHS, const FHeroEmoteData& RHS)
{
	return LHS.ID == RHS.ID;
}
