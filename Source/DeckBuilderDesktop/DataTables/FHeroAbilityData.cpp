
#include "DeckBuilderDesktop.h"
#include "FHeroAbilityData.h"

bool operator == (const FHeroAbilityData& LHS, const FHeroAbilityData& RHS)
{
	return LHS.AbilityName.Equals(RHS.AbilityName);
}
