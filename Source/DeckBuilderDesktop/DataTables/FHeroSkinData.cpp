
#include "DeckBuilderDesktop.h"
#include "FHeroSkinData.h"

bool operator == (const FHeroSkinData& LHS, const FHeroSkinData& RHS)
{
	return LHS.SkinName.Equals(RHS.SkinName);
}
