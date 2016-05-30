
#include "DeckBuilderDesktop.h"
#include "FRewardData.h"

bool operator == (const FRewardData& LHS, const FRewardData& RHS)
{
	return LHS.RewardName == RHS.RewardName;
}
