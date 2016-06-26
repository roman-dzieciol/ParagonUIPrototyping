
#include "DeckBuilderDesktop.h"
#include "FStoreProductData.h"

bool operator == (const FStoreProductData& LHS, const FStoreProductData& RHS)
{
	return LHS.ID == RHS.ID;
}
