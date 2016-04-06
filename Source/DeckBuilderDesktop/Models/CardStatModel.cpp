
#include "DeckBuilderDesktop.h"
#include "CardStatModel.h"

UCardStatModel::UCardStatModel(class FObjectInitializer const & ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool operator == (const UCardStatModel& LHS, const UCardStatModel& RHS)
{
	return LHS.Type.EqualTo(RHS.Type)
		&& LHS.Value.EqualTo(RHS.Value)
		&& LHS.Icon == RHS.Icon;
}
