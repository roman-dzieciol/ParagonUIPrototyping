// Fill out your copyright notice in the Description page of Project Settings.

#include "DeckBuilderDesktop.h"
#include "CardFilterFactory.h"
#include "Filters/CardFilterByStat.h"


UCardFilter* UCardFilterFactory::ConstructFilterByCostValue(int32 CostValue)
{
	UCardFilterByStat* CostFilter = NewObject<UCardFilterByStat>(GetTransientPackage(), NAME_None);
	CostFilter->FilterName = FName(TEXT("Cost"));
	CostFilter->StatName = TEXT("Cost");
	CostFilter->StatContains = FString::FromInt(CostValue);
	CostFilter->bEqualValue = true;
	return CostFilter;
}
