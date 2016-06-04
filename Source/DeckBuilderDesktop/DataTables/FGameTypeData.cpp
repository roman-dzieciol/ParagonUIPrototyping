
#include "DeckBuilderDesktop.h"
#include "FGameTypeData.h"

bool operator == (const FGameTypeData& LHS, const FGameTypeData& RHS)
{
	return LHS.GameTypeName.Equals(RHS.GameTypeName);
}
