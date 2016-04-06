
#include "DeckBuilderDesktop.h"
#include "FStatData.h"

bool operator == (const FStatData& LHS, const FStatData& RHS)
{
	return LHS.StatName == RHS.StatName
		&& LHS.FilterGroup == RHS.FilterGroup
		&& LHS.FilterGroupIndex == RHS.FilterGroupIndex
		&& LHS.BonusType == RHS.BonusType
		&& LHS.Icon == RHS.Icon
		&& LHS.Reserved == RHS.Reserved;
}
