
#include "DeckBuilderDesktop.h"
#include "FHeroData.h"

bool operator == (const FHeroData& LHS, const FHeroData& RHS)
{
	return LHS.HeroName.EqualTo(RHS.HeroName)
		&& LHS.AvatarTexture == RHS.AvatarTexture;
}
