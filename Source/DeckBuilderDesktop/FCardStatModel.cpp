
#include "DeckBuilderDesktop.h"
#include "FCardStatModel.h"

bool operator == (const FCardStatModel& LHS, const FCardStatModel& RHS)
{
	return LHS.Type == RHS.Type
		&& LHS.Value == RHS.Value
		&& LHS.Icon == RHS.Icon;
}
