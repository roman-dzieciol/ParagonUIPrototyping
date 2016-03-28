
#include "DeckBuilderDesktop.h"
#include "FStatData.h"

bool operator == (const FStatData& LHS, const FStatData& RHS)
{
	return LHS.StatName == RHS.StatName
		&& LHS.FilterGroup == RHS.FilterGroup
		&& LHS.FilterGroupIndex == RHS.FilterGroupIndex
		&& LHS.Reserved == RHS.Reserved;
}
